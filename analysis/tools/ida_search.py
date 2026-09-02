#!/usr/bin/env python3
# ida_search.py — targeted SEARCH over the IDB. Cheap questions the model asks a lot,
# answered without decompiling everything. Writes JSON to a file.
#
# INVOKE:
#   idat.exe -A -Lida_s.log -S"ida_search.py <OUT.json> <mode> [param]" <lib.so>
#
# MODES:
#   svc            — every ARM SVC/syscall site (kill-chain: exit_group/kill). Reports the
#                    preceding R7 immediate (the syscall number) when found. Ref: binaryhax0r.
#   imm <value>    — every instruction whose operand == <value> (hex or dec). Finds refs to a
#                    magic constant / offset (e.g. a config flag, a struct offset).
#   bytes <hex>    — byte-pattern search, e.g. "0F B4 2D E5". Returns matching addrs+func.
#   str <substr>   — case-insensitive substring over the IDB string list (already-plaintext
#                    strings only; encrypted ones need ida_decoder_args.py).
#   callers <name> — every function that calls <name/ea> (xref map, with caller names).

import json, sys
import idaapi, idautils, idc, ida_funcs, ida_name, ida_bytes, ida_nalt, ida_allins

idaapi.auto_wait()

args = idc.ARGV[1:] if hasattr(idc, "ARGV") else []
OUT  = args[0] if args else "search.json"
MODE = args[1] if len(args) > 1 else ""
PARAM = args[2] if len(args) > 2 else ""

def func_at(ea):
    f = ida_funcs.get_func(ea)
    return (f.start_ea if f else 0, ida_name.get_ea_name(f.start_ea) if f else "")

out = []

if MODE == "svc":
    for seg_ea in idautils.Segments():
        seg = idaapi.getseg(seg_ea)
        if not seg or not (seg.perm & idaapi.SEGPERM_EXEC):
            continue
        ea = seg.start_ea
        while ea < seg.end_ea:
            try:
                insn = idaapi.insn_t()
                if idaapi.decode_insn(insn, ea) and insn.itype == ida_allins.ARM_svc:
                    # backtrack for R7 = syscall number
                    r7 = None
                    cur = idc.prev_head(ea); steps = 0
                    while cur != idc.BADADDR and steps < 8:
                        if idc.print_operand(cur, 0) == "R7" and idc.print_insn_mnem(cur) in ("MOV", "MOVS", "MOVW", "LDR"):
                            r7 = idc.get_operand_value(cur, 1); break
                        cur = idc.prev_head(cur); steps += 1
                    fa, fn = func_at(ea)
                    out.append({"ea": ea, "func_ea": fa, "func": fn,
                                "r7_syscall": r7, "r7_hex": ("0x%X" % r7) if isinstance(r7, int) else None})
            except Exception:
                pass
            ea = idc.next_head(ea, seg.end_ea)

elif MODE == "imm":
    try:
        target = int(PARAM, 16) if PARAM.lower().startswith("0x") else int(PARAM)
    except Exception:
        target = None
    if target is not None:
        for seg_ea in idautils.Segments():
            seg = idaapi.getseg(seg_ea)
            if not seg or not (seg.perm & idaapi.SEGPERM_EXEC):
                continue
            ea = seg.start_ea
            while ea < seg.end_ea:
                for opn in range(3):
                    try:
                        if idc.get_operand_value(ea, opn) == target:
                            fa, fn = func_at(ea)
                            out.append({"ea": ea, "func_ea": fa, "func": fn,
                                        "insn": idc.generate_disasm_line(ea, 0)})
                            break
                    except Exception:
                        pass
                ea = idc.next_head(ea, seg.end_ea)

elif MODE == "bytes":
    pat = PARAM
    ea = idaapi.inf_get_min_ea()
    end = idaapi.inf_get_max_ea()
    while True:
        found = ida_bytes.find_bytes(pat, ea) if hasattr(ida_bytes, "find_bytes") else idc.find_binary(ea, idc.SEARCH_DOWN, pat)
        if found == idc.BADADDR or found is None:
            break
        fa, fn = func_at(found)
        out.append({"ea": found, "func_ea": fa, "func": fn})
        ea = found + 1
        if len(out) > 500:
            break

elif MODE == "str":
    needle = PARAM.lower()
    sc = idautils.Strings()
    sc.setup(strtypes=[ida_nalt.STRTYPE_C, ida_nalt.STRTYPE_C_16])
    for s in sc:
        try:
            v = str(s)
        except Exception:
            continue
        if needle in v.lower():
            refs = [xr.frm for xr in idautils.XrefsTo(s.ea, 0)]
            out.append({"ea": s.ea, "value": v, "xrefs": refs[:16]})

elif MODE == "callers":
    tgt = idc.get_name_ea_simple(PARAM)
    if tgt == idc.BADADDR:
        try: tgt = int(PARAM, 16)
        except Exception: tgt = idc.BADADDR
    if tgt != idc.BADADDR:
        for ref in idautils.CodeRefsTo(tgt, 0):
            fa, fn = func_at(ref)
            out.append({"call_site": ref, "func_ea": fa, "func": fn,
                        "insn": idc.generate_disasm_line(ref, 0)})

with open(OUT, "w", encoding="utf-8") as f:
    json.dump(out, f, indent=0)
print("[search] mode=%s param=%s -> %d hits -> %s" % (MODE, PARAM, len(out), OUT))
idc.qexit(0)
