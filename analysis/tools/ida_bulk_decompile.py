#!/usr/bin/env python3
# ida_bulk_decompile.py — Haruspex pattern: decompile EVERY function to its own file.
# Run ONCE per lib (background, slow). Produces analysis/<lib>/RAW/decomp/<name>.c so the
# faster model can grep pseudocode across the whole lib WITHOUT any further IDA round-trip.
#
# INVOKE:
#   idat.exe -A -Lida_bulk.log -S"ida_bulk_decompile.py <OUT_DIR>" <lib.so>
#
# Also writes ALL.c (concatenation) and index.tsv (name<TAB>ea<TAB>size<TAB>file).
# Skips thunks/tiny funcs to keep the corpus meaningful. Safe to interrupt/resume.

import os, re
import idaapi, idautils, idc, ida_hexrays, ida_funcs, ida_name

idaapi.auto_wait()
if not ida_hexrays.init_hexrays_plugin():
    print("[bulk] hexrays unavailable — aborting"); idc.qexit(1)

OUT = idc.ARGV[1] if len(idc.ARGV) > 1 else "."
DEC = os.path.join(OUT, "decomp")
os.makedirs(DEC, exist_ok=True)

def safe(name):
    return re.sub(r"[^A-Za-z0-9_.-]", "_", name)[:120]

idx = []
all_fh = open(os.path.join(OUT, "ALL.c"), "w", encoding="utf-8")
n = 0
for ea in idautils.Functions():
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    size = f.end_ea - f.start_ea
    if size < 12:            # skip trivial thunks
        continue
    name = ida_name.get_ea_name(ea) or ("sub_%X" % ea)
    try:
        cf = ida_hexrays.decompile(ea)
        code = str(cf) if cf else "// decompile failed @0x%X\n" % ea
    except Exception as e:
        code = "// error @0x%X: %s\n" % (ea, e)
    fn = os.path.join(DEC, "%s_%X.c" % (safe(name), ea))
    hdr = "// %s @ 0x%X  size=%d\n" % (name, ea, size)
    with open(fn, "w", encoding="utf-8") as fh:
        fh.write(hdr + code)
    all_fh.write("\n\n// ==== %s @ 0x%X ====\n" % (name, ea) + code)
    idx.append("%s\t0x%X\t%d\t%s" % (name, ea, size, os.path.relpath(fn, OUT)))
    n += 1
    if n % 200 == 0:
        print("[bulk] %d functions..." % n)

all_fh.close()
with open(os.path.join(OUT, "index.tsv"), "w", encoding="utf-8") as f:
    f.write("name\tea\tsize\tfile\n" + "\n".join(idx))
print("[bulk] DONE — %d functions decompiled to %s" % (n, DEC))
idc.qexit(0)
