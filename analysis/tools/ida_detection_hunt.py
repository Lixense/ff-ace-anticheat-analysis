#!/usr/bin/env python3
# ida_detection_hunt.py — TARGETED detection hunter. Replaces slow "decompile everything".
# We ONLY care about code that DETECTS US. This finds detection-relevant functions and
# decompiles ONLY those, fast.
#
# Strategy (all from the prebuilt .i64, no full-corpus decompile):
#   1. Scan plaintext strings for detection keywords (frida/xposed/lspatch/root/emu/cert/...).
#   2. For each hit, find the function(s) that reference it (xrefs) — those are detectors.
#   3. Decompile ONLY those detector functions to OUT_DIR/detectors.c.
#   4. Also flag functions that call the "interesting" libc imports (open/stat/access on
#      /proc, ptrace, kill) — the sensor primitives.
#   5. Emit detectors.json (machine-readable) so hist.py can ingest it into the .db.
#
# INVOKE:
#   idat.exe -A -Lhunt.log -S"ida_detection_hunt.py <OUT_DIR>" <lib.so>
#
# Output: OUT_DIR/detectors.json  (+ detectors.c pseudocode of only the detector funcs)

import os, json
import idaapi, idautils, idc, ida_hexrays, ida_funcs, ida_name, ida_nalt

idaapi.auto_wait()
HAVE_HR = ida_hexrays.init_hexrays_plugin()

OUT = idc.ARGV[1] if len(idc.ARGV) > 1 else "."
os.makedirs(OUT, exist_ok=True)

# Detection keyword taxonomy — ONLY things that matter to "how are we detected".
# type -> substrings (lowercased) that appear in ACE's detection strings.
KEYWORDS = {
    "hook":     ["frida", "gadget", "gum-js", "substrate", "sandhook", "hookzz", "dobby", "xhook", "whale", "inlinehook", "got_hook", "plt"],
    "xposed":   ["xposed", "de.robv", "lsposed", "edxposed", "riru", "lsplant", "modulemanager"],
    "lspatch":  ["lspatch", "npatch", "lspappcomponent", "metaloader", "patch-", "origin.apk", "liblspatch", "libnpatch"],
    "sigcert":  ["certificate", "getmodulus", "generatecertificate", "signature", "ispatch", "pmshook", "fucksign", "signinginfo", "getpackageinfo", "apk_hash", "cert"],
    "root":     ["magisk", "supersu", "kernelsu", "/su", "superuser", "zygisk", "kinguser", "busybox", "which su", "daemonsu", "eu.chainfire", "topjohnwu"],
    "emulator": ["bluestacks", "nox", "ldplayer", "mumu", "genymotion", "goldfish", "ranchu", "qemu", "vbox", "houdini", "x86", "virtpipe", "ro.kernel", "translator"],
    "vm":       ["virtual", "dualaid", "parallel", "vmos", "droidplugin", "com.lody", "chaos", "stubactivity", "sandbox", "clone"],
    "debug":    ["tracerpid", "ptrace", "debugger", "jdwp", "isdebuggerconnected", "ro.debuggable", "/proc/self/status"],
    "proc":     ["/proc/self/maps", "/proc/self/task", "/proc/self/fd", "/proc/self/cmdline", "/proc/self/comm", "/proc/self/environ", "/proc/self/mem", "map_files", "ns/mnt", "/proc/1/cgroup"],
    "report":   ["anticheatexpert", "corereport", "senddatatosvr", "gamesafe", "tdm", "donot_delete_me", "ob_cdn", "ob_cs2", "ob_gs"],
}

def kw_type(s):
    ls = s.lower()
    for t, subs in KEYWORDS.items():
        for sub in subs:
            if sub in ls:
                return t, sub
    return None, None

# 1+2: string hits -> referencing functions
detector_eas = {}   # ea -> {"reasons":[...], "types":set()}
string_hits = []
sc = idautils.Strings()
sc.setup(strtypes=[ida_nalt.STRTYPE_C, ida_nalt.STRTYPE_C_16])
for s in sc:
    try:
        val = str(s)
    except Exception:
        continue
    t, sub = kw_type(val)
    if not t:
        continue
    refs = []
    for xr in idautils.XrefsTo(s.ea, 0):
        f = ida_funcs.get_func(xr.frm)
        if f:
            refs.append(f.start_ea)
            d = detector_eas.setdefault(f.start_ea, {"reasons": [], "types": set()})
            d["reasons"].append("str:%s@0x%X (%s)" % (val[:40], s.ea, t))
            d["types"].add(t)
    string_hits.append({"ea": s.ea, "value": val, "type": t, "match": sub, "func_refs": refs})

# 4: functions calling sensor libc primitives
SENSOR_IMPORTS = {"ptrace", "kill", "tgkill", "syscall", "fork"}
# (open/stat/access are too common to flag wholesale; the string-xref pass already catches
#  the /proc ones via the "proc" keyword group.)
for m in range(idaapi.get_import_module_qty()):
    def cb(ea, name, ord_, _m=m):
        if name and name.split("@")[0] in SENSOR_IMPORTS:
            for xr in idautils.XrefsTo(ea, 0):
                f = ida_funcs.get_func(xr.frm)
                if f:
                    d = detector_eas.setdefault(f.start_ea, {"reasons": [], "types": set()})
                    d["reasons"].append("calls %s" % name)
                    d["types"].add("debug" if name.split("@")[0] in ("ptrace",) else "kill")
        return True
    idaapi.enum_import_names(m, cb)

# 3: decompile ONLY detector functions
detectors = []
cfile = open(os.path.join(OUT, "detectors.c"), "w", encoding="utf-8")
for ea, info in sorted(detector_eas.items()):
    nm = ida_name.get_ea_name(ea) or ("sub_%X" % ea)
    code = ""
    if HAVE_HR:
        try:
            cf = ida_hexrays.decompile(ea)
            code = str(cf) if cf else "// decompile failed\n"
        except Exception as e:
            code = "// error: %s\n" % e
    cfile.write("\n// ==== %s @ 0x%X  types=%s ====\n" % (nm, ea, ",".join(sorted(info["types"]))))
    for r in info["reasons"][:12]:
        cfile.write("//   reason: %s\n" % r)
    cfile.write(code)
    detectors.append({
        "ea": ea, "name": nm,
        "types": sorted(info["types"]),
        "reasons": info["reasons"][:20],
    })
cfile.close()

with open(os.path.join(OUT, "detectors.json"), "w", encoding="utf-8") as f:
    json.dump({"detector_functions": detectors, "string_hits": string_hits}, f, indent=0, ensure_ascii=False)

print("[hunt] %d detector functions, %d detection strings -> %s" %
      (len(detectors), len([h for h in string_hits if h["type"]]), OUT))
idc.qexit(0)
