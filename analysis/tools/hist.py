#!/usr/bin/env python3
# hist.py — the searchable History database. ONE SQLite file collects everything the
# analysis fleet finds, so agents record + query findings FAST without re-reading big .md.
#
# DB: analysis/History/ace.db   (sqlite3, stdlib — zero install)
#
# The whole project has ONE question: "what detects US, and how do we avoid it with the
# smali method?" So the schema is detection-first.
#
# TABLES
#   detections  — THE catalog of what ACE looks for (frida/xposed/lspatch/root/emu/cert/file/...)
#                 This is the avoid-list for our smali build. Each row = one thing ACE checks.
#   findings    — reverse-eng findings (a function/flag/offset that matters to detection or kill)
#   runs        — audit log of every analysis action (what was done, when, how long)
#
# USAGE (agents call these):
#   python analysis/tools/hist.py init
#   python analysis/tools/hist.py add-detection --lib libanogs --type cert --target getModulus \
#          --string-ea 0x109abc --by-func ace_cert_scan --affects-us 1 --decoded 1 \
#          --avoid "our re-sign trips this; smali build must keep original cert or hide read"
#   python analysis/tools/hist.py add-finding --lib libanogs --category kill --name exit_group_site \
#          --offset 0x1CE750 --isa thumb --affects-us 1 --severity high \
#          --summary "raw svc exit_group kill" --evidence "search svc; decomp/..._1CE750.c"
#   python analysis/tools/hist.py log-run --lib libanogs --action decompile --args "AnoSDKInit" \
#          --output analysis/libanogs/RAW/x.txt --seconds 2
#   python analysis/tools/hist.py search cert            # full-text over all tables
#   python analysis/tools/hist.py detections --affects-us 1   # the avoid-list
#   python analysis/tools/hist.py report                 # summary counts + top findings

import argparse, os, sqlite3, sys, time, json

DB_DIR = os.path.join(os.path.dirname(__file__), "..", "History")
DB_DIR = os.path.abspath(DB_DIR)
DB = os.path.join(DB_DIR, "ace.db")

SCHEMA = """
CREATE TABLE IF NOT EXISTS detections (
  id INTEGER PRIMARY KEY,
  lib TEXT, type TEXT,            -- frida|xposed|lspatch|npatch|root|emulator|cert|file|debug|vm|hook|other
  target TEXT,                    -- the concrete string/class/pkg/path ACE looks for
  string_ea TEXT,                 -- where the (decoded) string lives, if known
  by_func TEXT,                   -- function that references/uses it
  by_func_ea TEXT,
  decoded INTEGER DEFAULT 0,      -- 1 if we recovered it from encrypted form
  affects_us INTEGER DEFAULT 0,   -- 1 if OUR smali build would trip it
  avoid TEXT,                     -- how we avoid it in the smali method
  created_at TEXT
);
CREATE TABLE IF NOT EXISTS findings (
  id INTEGER PRIMARY KEY,
  lib TEXT, category TEXT,        -- kill|report|init|export|jni|scanner|string|integrity|other
  name TEXT, offset TEXT, isa TEXT,
  affects_us INTEGER DEFAULT 0,
  severity TEXT,                  -- high|med|low
  summary TEXT, evidence TEXT,
  mission TEXT, agent TEXT,
  created_at TEXT
);
CREATE TABLE IF NOT EXISTS runs (
  id INTEGER PRIMARY KEY,
  lib TEXT, action TEXT, args TEXT, output TEXT, seconds REAL, created_at TEXT
);
CREATE INDEX IF NOT EXISTS i_det_type ON detections(type);
CREATE INDEX IF NOT EXISTS i_det_us   ON detections(affects_us);
CREATE INDEX IF NOT EXISTS i_fnd_cat  ON findings(category);
"""

def conn():
    os.makedirs(DB_DIR, exist_ok=True)
    c = sqlite3.connect(DB)
    c.row_factory = sqlite3.Row
    return c

def now():
    return time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())

def cmd_init(a):
    c = conn(); c.executescript(SCHEMA); c.commit()
    print("[hist] initialized", DB)

def cmd_add_detection(a):
    c = conn(); c.executescript(SCHEMA)
    c.execute("""INSERT INTO detections(lib,type,target,string_ea,by_func,by_func_ea,decoded,affects_us,avoid,created_at)
                 VALUES(?,?,?,?,?,?,?,?,?,?)""",
              (a.lib, a.type, a.target, a.string_ea, a.by_func, a.by_func_ea,
               a.decoded, a.affects_us, a.avoid, now()))
    c.commit(); print("[hist] +detection:", a.type, a.target)

def cmd_add_finding(a):
    c = conn(); c.executescript(SCHEMA)
    c.execute("""INSERT INTO findings(lib,category,name,offset,isa,affects_us,severity,summary,evidence,mission,agent,created_at)
                 VALUES(?,?,?,?,?,?,?,?,?,?,?,?)""",
              (a.lib, a.category, a.name, a.offset, a.isa, a.affects_us, a.severity,
               a.summary, a.evidence, a.mission, a.agent, now()))
    c.commit(); print("[hist] +finding:", a.category, a.name, a.offset or "")

def cmd_log_run(a):
    c = conn(); c.executescript(SCHEMA)
    c.execute("INSERT INTO runs(lib,action,args,output,seconds,created_at) VALUES(?,?,?,?,?,?)",
              (a.lib, a.action, a.args, a.output, a.seconds, now()))
    c.commit(); print("[hist] +run:", a.action, a.args or "")

def cmd_search(a):
    c = conn(); c.executescript(SCHEMA)
    q = "%%%s%%" % a.query
    print("== detections ==")
    for r in c.execute("""SELECT lib,type,target,by_func,affects_us,avoid FROM detections
                          WHERE target LIKE ? OR by_func LIKE ? OR avoid LIKE ? OR type LIKE ?""",
                        (q, q, q, q)):
        print(" [%s] %-9s %-30s by=%s us=%s" % (r["lib"], r["type"], (r["target"] or "")[:30], r["by_func"], r["affects_us"]))
        if r["avoid"]: print("        avoid:", r["avoid"])
    print("== findings ==")
    for r in c.execute("""SELECT lib,category,name,offset,severity,affects_us,summary FROM findings
                          WHERE name LIKE ? OR summary LIKE ? OR evidence LIKE ? OR category LIKE ?""",
                        (q, q, q, q)):
        print(" [%s] %-9s %-24s %-10s sev=%s us=%s" % (r["lib"], r["category"], (r["name"] or "")[:24], r["offset"] or "", r["severity"], r["affects_us"]))
        if r["summary"]: print("        ", r["summary"])

def cmd_detections(a):
    c = conn(); c.executescript(SCHEMA)
    where, args = "1=1", []
    if a.affects_us is not None:
        where += " AND affects_us=?"; args.append(a.affects_us)
    if a.type:
        where += " AND type=?"; args.append(a.type)
    rows = list(c.execute("SELECT * FROM detections WHERE %s ORDER BY affects_us DESC,type" % where, args))
    print("== %d detections ==" % len(rows))
    for r in rows:
        flag = "[US]" if r["affects_us"] else "    "
        print("%s [%s] %-9s %-32s by=%s" % (flag, r["lib"], r["type"], (r["target"] or "")[:32], r["by_func"] or ""))
        if r["avoid"]: print("       avoid:", r["avoid"])

def cmd_report(a):
    c = conn(); c.executescript(SCHEMA)
    def one(q, args=()):
        return c.execute(q, args).fetchone()[0]
    print("=== History report (%s) ===" % DB)
    print("detections total:", one("SELECT COUNT(*) FROM detections"),
          "| affects-us:", one("SELECT COUNT(*) FROM detections WHERE affects_us=1"))
    print("findings total:  ", one("SELECT COUNT(*) FROM findings"),
          "| high-sev:", one("SELECT COUNT(*) FROM findings WHERE severity='high'"))
    print("runs logged:     ", one("SELECT COUNT(*) FROM runs"))
    print("\n-- detections by type --")
    for r in c.execute("SELECT type,COUNT(*) n,SUM(affects_us) us FROM detections GROUP BY type ORDER BY n DESC"):
        print("  %-10s %3d  (affects-us %s)" % (r["type"], r["n"], r["us"] or 0))
    print("\n-- things that detect US (the smali avoid-list) --")
    for r in c.execute("SELECT lib,type,target,avoid FROM detections WHERE affects_us=1 ORDER BY type"):
        print("  [%s] %-9s %s" % (r["lib"], r["type"], (r["target"] or "")[:40]))
        if r["avoid"]: print("       ->", r["avoid"])

def main():
    p = argparse.ArgumentParser()
    sub = p.add_subparsers(dest="cmd", required=True)
    sub.add_parser("init")

    d = sub.add_parser("add-detection")
    for f in ("lib","type","target","string-ea","by-func","by-func-ea","avoid"):
        d.add_argument("--"+f, default="")
    d.add_argument("--decoded", type=int, default=0)
    d.add_argument("--affects-us", type=int, default=0)

    f = sub.add_parser("add-finding")
    for k in ("lib","category","name","offset","isa","severity","summary","evidence","mission","agent"):
        f.add_argument("--"+k, default="")
    f.add_argument("--affects-us", type=int, default=0)

    r = sub.add_parser("log-run")
    for k in ("lib","action","args","output"):
        r.add_argument("--"+k, default="")
    r.add_argument("--seconds", type=float, default=0)

    s = sub.add_parser("search"); s.add_argument("query")
    dd = sub.add_parser("detections")
    dd.add_argument("--affects-us", type=int, default=None)
    dd.add_argument("--type", default=None)
    sub.add_parser("report")

    a = p.parse_args()
    # normalize dashed dests
    for attr in list(vars(a)):
        if "-" in attr:
            setattr(a, attr.replace("-","_"), getattr(a, attr))
    {"init":cmd_init,"add-detection":cmd_add_detection,"add-finding":cmd_add_finding,
     "log-run":cmd_log_run,"search":cmd_search,"detections":cmd_detections,"report":cmd_report}[a.cmd](a)

if __name__ == "__main__":
    main()
