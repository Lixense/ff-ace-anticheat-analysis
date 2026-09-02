#!/usr/bin/env bash
# ida.sh — the ONE entry point every agent uses to drive IDA. Wraps idat.exe batch mode,
# handles TVHEADLESS, .i64 reuse, and per-lib output dirs. Never opens a GUI.
#
# Usage:
#   analysis/tools/ida.sh <lib>  inventory                 # ONE-TIME bulk JSON dump (+builds .i64)
#   analysis/tools/ida.sh <lib>  bulk                       # ONE-TIME decompile-every-function
#   analysis/tools/ida.sh <lib>  decompile <out.txt> <t1,t2,...>
#   analysis/tools/ida.sh <lib>  args <out.json> <decoder> [argidx]
#   analysis/tools/ida.sh <lib>  search <out.json> <mode> [param]
#
# <lib> = libanogs | libanort | libmain   (folder under analysis/)
# All output paths are relative to analysis/<lib>/  unless absolute.
set -euo pipefail

# Point ROOT at the repo root (where analysis/ sits), and IDAT at your idat.exe.
# Override via env, e.g. ROOT=/d/work/ff-ace IDAT=/c/.../idat.exe ./ida.sh ...
ROOT="${ROOT:-$(cd "$(dirname "$0")/../.." && pwd)}"
IDAT="${IDAT:-/c/Program Files/IDA Professional 9.4/idat.exe}"
TOOLS="$ROOT/analysis/tools"
export TVHEADLESS=1

LIB="${1:?lib name: libanogs|libanort|libmain}"
ACTION="${2:?action: inventory|bulk|decompile|args|search}"
LIBDIR="$ROOT/analysis/$LIB"
SO="$LIBDIR/$LIB.so"
[ -f "$SO" ] || { echo "ERROR: $SO not found"; exit 2; }

cd "$LIBDIR"

run_ida() {  # run_ida <script> <args...>
  local script="$1"; shift
  local log="$LIBDIR/RAW/$(basename "$script" .py).log"
  # -A autonomous, -L log, -S"script args" (single token), target .so
  "$IDAT" -A -L"$log" -S"$TOOLS/$script $*" "$SO"
}

# Normalize an output path: if relative, anchor it under the current lib dir so callers
# can pass short names (jni.txt) OR absolute paths interchangeably.
abspath() {
  case "$1" in
    /*|[A-Za-z]:*) echo "$1" ;;           # already absolute (unix or windows drive)
    *) echo "$LIBDIR/$1" ;;
  esac
}

case "$ACTION" in
  inventory)
    echo "[ida.sh] $LIB inventory -> RAW/  (first run auto-analyzes; slow)"
    run_ida ida_inventory.py "$LIBDIR/RAW"
    ;;
  bulk)
    echo "[ida.sh] $LIB bulk decompile -> RAW/decomp/  (SLOW — 23k funcs; prefer 'hunt')"
    run_ida ida_bulk_decompile.py "$LIBDIR/RAW"
    ;;
  hunt)
    echo "[ida.sh] $LIB detection-hunt -> RAW/detectors.{json,c}  (fast, targeted)"
    run_ida ida_detection_hunt.py "$LIBDIR/RAW"
    ;;
  decompile)
    OUT="$(abspath "${3:?out file}")"; TGT="${4:?targets csv}"
    run_ida ida_decompile.py "$OUT" "$TGT"
    echo "[ida.sh] wrote $OUT"
    ;;
  args)
    OUT="$(abspath "${3:?out json}")"; DEC="${4:?decoder}"; IDX="${5:-0}"
    run_ida ida_decoder_args.py "$OUT" "$DEC" "$IDX"
    echo "[ida.sh] wrote $OUT"
    ;;
  search)
    OUT="$(abspath "${3:?out json}")"; MODE="${4:?mode}"; PARAM="${5:-}"
    run_ida ida_search.py "$OUT" "$MODE" "$PARAM"
    echo "[ida.sh] wrote $OUT"
    ;;
  *)
    echo "unknown action: $ACTION"; exit 2;;
esac
