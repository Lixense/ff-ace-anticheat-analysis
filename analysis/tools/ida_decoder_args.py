#!/usr/bin/env python3
# ida_decoder_args.py — STRING-DECODER ARGUMENT RECOVERY (Augur / Unit42 pattern).
#
# ACE strings are XOR-encrypted; the plaintext only appears when a decoder fn is called
# with an integer string-ID. This script, given a decoder function, dumps every call site
# and the integer argument passed — producing the "call_site -> string_id" map that lets
# us decode the whole table offline (reimplement the XOR in Python once the algo is known).
#
# Ref: unit42 "IDAPython string obfuscation", reverseengineering.SE 11332, RevEng.AI StealC.
# CPU-agnostic arg discovery via ida_typeinf.get_arg_addrs, with an ARM MOV/MOVW+MOVT/LDR
# backtrack fallback (R0..R3).
#
# INVOKE:
#   idat.exe -A -Lida_da.log -S"ida_decoder_args.py <OUT.json> <decoder_name_or_ea> [argидx]" <lib.so>
# e.g.  ...ida_decoder_args.py anogs_decoder0.json 0x36D764 0
#
# OUTPUT: JSON [ {call_site, caller_ea, caller_name, arg0, arg0_hex} ... ]

import json
import idaapi, idautils, idc, ida_funcs, ida_name, ida_typeinf

idaapi.auto_wait()

args = idc.ARGV[1:] if hasattr(idc, "ARGV") else []
OUT  = args[0] if args else "decoder_args.json"
TGT  = args[1] if len(args) > 1 else None
AIDX = int(args[2]) if len(args) > 2 else 0

if TGT is None:
    open(OUT, "w").write("[]")
    print("[da] no target given"); idc.qexit(1)

ea = idc.get_name_ea_simple(TGT)
if ea == idc.BADADDR:
    try:
        ea = int(TGT, 16) if TGT.lower().startswith("0x") else int(TGT)
    except Exception:
        ea = idc.BADADDR
if ea == idc.BADADDR:
    open(OUT, "w").write("[]")
    print("[da] cannot resolve %s" % TGT); idc.qexit(1)

ARG_REGS = ["R0", "R1", "R2", "R3"]

def imm_via_get_arg_addrs(call_ea):
    """CPU-agnostic: IDA tells us where each arg is prepared."""
    try:
        addrs = ida_typeinf.get_arg_addrs(call_ea)
    except Exception:
        addrs = None
    if not addrs or AIDX >= len(addrs):
        return None
    prep = addrs[AIDX]
    v = idc.get_operand_value(prep, 1)
    if v is not None and v != -1:
        return v
    return None

def imm_via_backtrack(call_ea):
    """ARM fallback: walk back ~10 insns, track last immediate into the arg register."""
    want = ARG_REGS[AIDX] if AIDX < len(ARG_REGS) else "R0"
    cur = idc.prev_head(call_ea)
    steps = 0
    hi = lo = None
    while cur != idc.BADADDR and steps < 12:
        mnem = idc.print_insn_mnem(cur)
        op0  = idc.print_operand(cur, 0)
        if op0 == want:
            if mnem in ("MOV", "MOVS", "MOVW", "LDR"):
                v = idc.get_operand_value(cur, 1)
                if mnem == "MOVW":
                    lo = v & 0xFFFF
                    return (hi << 16 | lo) if hi is not None else lo
                return v
            if mnem == "MOVT":
                hi = idc.get_operand_value(cur, 1) & 0xFFFF
        cur = idc.prev_head(cur)
        steps += 1
    return None

results = []
for ref in idautils.CodeRefsTo(ea, 0):
    mnem = idc.print_insn_mnem(ref)
    if mnem not in ("BL", "BLX", "B", "CALL"):
        continue
    val = imm_via_get_arg_addrs(ref)
    if val is None:
        val = imm_via_backtrack(ref)
    cf = ida_funcs.get_func(ref)
    results.append({
        "call_site": ref,
        "caller_ea": cf.start_ea if cf else 0,
        "caller_name": ida_name.get_ea_name(cf.start_ea) if cf else "",
        "arg0": val,
        "arg0_hex": ("0x%X" % val) if isinstance(val, int) else None,
    })

with open(OUT, "w", encoding="utf-8") as f:
    json.dump(results, f, indent=0)
got = sum(1 for r in results if r["arg0"] is not None)
print("[da] %s: %d call sites, %d args recovered -> %s" % (TGT, len(results), got, OUT))
idc.qexit(0)
