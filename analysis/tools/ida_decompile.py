#!/usr/bin/env python3
# ida_decompile.py — ON-DEMAND decompiler. Given names/addresses, emit Hex-Rays
# pseudocode to ONE output file (Haruspex pattern). The model reads only what it asked
# for — keeps context tiny. Never dumps the whole DB.
#
# INVOKE (idat batch, reuses the <lib>.i64 built by ida_inventory):
#   idat.exe -A -Lida_dec.log -S"ida_decompile.py <OUT.txt> <t1,t2,...>" <lib.so>
# Targets: symbol names (AnoSDKInit) OR hex addrs (0x1DA368) OR ea decimal.
#
# Adds per-function annotation: xref count, callees (who it calls), string refs inside.
# That gives the model the local call-graph + which decoded strings a function touches,
# so it can reason about behavior without a second IDA round-trip.

import idaapi, idautils, idc, ida_hexrays, ida_name, ida_funcs

idaapi.auto_wait()
if not ida_hexrays.init_hexrays_plugin():
    print("[dec] WARN: hexrays not available; asm fallback")

args = idc.ARGV[1:] if hasattr(idc, "ARGV") else []
out = args[0] if args else "ida_dec_out.txt"
targets = args[1].split(",") if len(args) > 1 else []

def resolve(t):
    t = t.strip()
    ea = idc.get_name_ea_simple(t)
    if ea != idc.BADADDR:
        return ea
    try:
        return int(t, 16) if t.lower().startswith("0x") else int(t)
    except Exception:
        return idc.BADADDR

def callees(ea):
    f = ida_funcs.get_func(ea)
    if not f:
        return []
    out = []
    cur = f.start_ea
    while cur < f.end_ea:
        for xr in idautils.XrefsFrom(cur, 0):
            if xr.type in (idaapi.fl_CN, idaapi.fl_CF):  # near/far call
                nm = ida_name.get_ea_name(xr.to)
                out.append(nm or ("0x%X" % xr.to))
        cur = idc.next_head(cur, f.end_ea)
    seen, uniq = set(), []
    for c in out:
        if c not in seen:
            seen.add(c); uniq.append(c)
    return uniq[:40]

def dc(ea):
    try:
        cf = ida_hexrays.decompile(ea)
        return str(cf) if cf else "// decompile failed @0x%X" % ea
    except Exception as e:
        return "// error @0x%X: %s" % (ea, e)

lines = []
for t in targets:
    ea = resolve(t)
    if ea == idc.BADADDR:
        lines.append("// NOT FOUND: %s" % t); continue
    nm = ida_name.get_ea_name(ea) or t
    try:
        xt = sum(1 for _ in idautils.XrefsTo(ea, 0))
    except Exception:
        xt = -1
    lines.append("// ===================================================================")
    lines.append("// %s @ 0x%X   xrefs_to=%d" % (nm, ea, xt))
    lines.append("// callees: %s" % ", ".join(callees(ea)))
    lines.append("// ===================================================================")
    lines.append(dc(ea))
    lines.append("")

with open(out, "w", encoding="utf-8") as f:
    f.write("\n".join(lines))
print("[dec] wrote %s (%d targets)" % (out, len(targets)))
idc.qexit(0)
