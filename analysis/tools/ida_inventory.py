#!/usr/bin/env python3
# ida_inventory.py — ONE-TIME bulk extractor. Dumps the whole IDB to JSON files.
# Run once per lib after auto-analysis. The faster model then works from these files
# (grep/read) for hours WITHOUT re-touching IDA. This is the "get everything out once"
# step (Augur pattern: strings cross-referenced to the code that uses them).
#
# INVOKE (idat batch — proven, no EULA gotcha):
#   idat.exe -A -Lida_inv.log -S"ida_inventory.py <OUT_DIR>" <lib.so>
# On first run IDA auto-analyzes (slow, minutes) then this dumps. Reuses <lib>.i64 after.
#
# OUTPUT (all in OUT_DIR):
#   functions.json   every function: ea,name,size,thumb,xrefs_to,is_export
#   strings.json     every string: ea,type,len,value,xrefs[]  (who references it)
#   imports.json     UND dynsym (external libc/libdl calls ACE makes)
#   exports.json     defined dynsym FUNCs (the AnoSDK* / JNI_* API surface)
#   init_array.json  C++ constructors (ACE's boot sequence — runs before JNI_OnLoad)
#   segments.json    segment layout (for RVA<->file-offset math)
#   summary.json     counts + entrypoint list

import json, os, sys
import idaapi, idautils, idc
import ida_funcs, ida_name, ida_bytes, ida_segment, ida_nalt, ida_entry, ida_ida

idaapi.auto_wait()

OUT = idc.ARGV[1] if len(idc.ARGV) > 1 else "."
os.makedirs(OUT, exist_ok=True)

def w(fn, obj):
    p = os.path.join(OUT, fn)
    with open(p, "w", encoding="utf-8") as f:
        json.dump(obj, f, indent=0, ensure_ascii=False)
    print("[inv] wrote %s (%d items)" % (fn, len(obj) if hasattr(obj, "__len__") else 1))

def thumb_at(ea):
    try:
        return idc.get_sreg(ea, "T") == 1
    except Exception:
        return None

# ---- exports / imports via dynsym ----------------------------------------
export_eas = set()
exports = []
try:
    import ida_nalt
    n = ida_nalt.get_import_module_qty()
except Exception:
    pass

# entrypoints (dynsym exports show up as entries in ELF)
for i in range(ida_entry.get_entry_qty()):
    ord_ = ida_entry.get_entry_ordinal(i)
    ea = ida_entry.get_entry(ord_)
    nm = ida_entry.get_entry_name(ord_)
    if ea != idc.BADADDR and nm:
        export_eas.add(ea)
        exports.append({"ea": ea, "name": nm, "thumb": thumb_at(ea)})
w("exports.json", exports)

# imports: iterate import modules
imports = []
def imp_cb(ea, name, ordinal):
    imports.append({"ea": ea, "name": name or "", "ord": ordinal})
    return True
try:
    for m in range(idaapi.get_import_module_qty()):
        idaapi.enum_import_names(m, imp_cb)
except Exception as e:
    print("[inv] import enum error:", e)
w("imports.json", imports)

# ---- functions -----------------------------------------------------------
funcs = []
for ea in idautils.Functions():
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    try:
        xt = sum(1 for _ in idautils.XrefsTo(ea, 0))
    except Exception:
        xt = -1
    funcs.append({
        "ea": ea,
        "name": ida_name.get_ea_name(ea),
        "size": f.end_ea - f.start_ea,
        "thumb": thumb_at(ea),
        "xrefs_to": xt,
        "is_export": ea in export_eas,
    })
w("functions.json", funcs)

# ---- strings + xrefs (Augur: correlate text with the code using it) ------
strings = []
try:
    sc = idautils.Strings()
    sc.setup(strtypes=[ida_nalt.STRTYPE_C, ida_nalt.STRTYPE_C_16])
    for s in sc:
        try:
            val = str(s)
        except Exception:
            val = ""
        refs = []
        for xr in idautils.XrefsTo(s.ea, 0):
            refs.append(xr.frm)
            if len(refs) >= 32:
                break
        strings.append({"ea": s.ea, "len": s.length, "type": s.strtype,
                        "value": val, "xrefs": refs})
except Exception as e:
    print("[inv] strings error:", e)
w("strings.json", strings)

# ---- init_array (C++ ctors — ACE's boot sequence) ------------------------
init_ctors = []
seg = ida_segment.get_segm_by_name(".init_array")
if seg:
    ea = seg.start_ea
    while ea < seg.end_ea:
        ptr = ida_bytes.get_dword(ea)  # 32-bit ARM
        if ptr and ptr != 0xFFFFFFFF:
            init_ctors.append({"slot_ea": ea, "target": ptr,
                              "target_name": ida_name.get_ea_name(ptr & ~1)})
        ea += 4
w("init_array.json", init_ctors)

# ---- segments ------------------------------------------------------------
segs = []
for s in idautils.Segments():
    seg = ida_segment.getseg(s)
    if seg:
        segs.append({"name": ida_segment.get_segm_name(seg),
                    "start": seg.start_ea, "end": seg.end_ea,
                    "perm": seg.perm})
w("segments.json", segs)

# ---- summary -------------------------------------------------------------
w("summary.json", {
    "functions": len(funcs),
    "strings": len(strings),
    "imports": len(imports),
    "exports": len(exports),
    "init_ctors": len(init_ctors),
    "segments": len(segs),
    "image_base": ida_ida.inf_get_min_ea(),
})
print("[inv] DONE")
idc.qexit(0)
