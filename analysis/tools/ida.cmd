@echo off
rem ida.cmd — Windows twin of ida.sh (bash unavailable in this CLI). Same CLI:
rem   analysis\tools\ida.cmd <lib> <action> [args...]
rem   actions: inventory | bulk | hunt | decompile <out> <targets_csv> | args <out> <decoder> [argidx] | search <out> <mode> [param]
rem   <out> may be relative (anchored under analysis\<lib>\) or absolute.
setlocal EnableDelayedExpansion
rem Point ROOT at the repo root (where analysis\ sits), and IDAT at your idat.exe.
rem Override by setting the env vars before calling, e.g.  set ROOT=D:\work\ff-ace  &  set IDAT=...
if not defined ROOT set ROOT=%~dp0..\..
if not defined IDAT set IDAT=C:\Program Files\IDA Professional 9.4\idat.exe
set TOOLS=%ROOT%\analysis\tools

set LIB=%1
set ACTION=%2
if "%LIB%"=="" echo ERROR: lib name: libanogs^|libanort^|libmain & exit /b 2
if "%ACTION%"=="" echo ERROR: action: inventory^|bulk^|hunt^|decompile^|args^|search & exit /b 2

set LIBDIR=%ROOT%\analysis\%LIB%
set SO=%LIBDIR%\%LIB%.so
if not exist "%SO%" echo ERROR: %SO% not found & exit /b 2
cd /d "%LIBDIR%"
set LOG=%LIBDIR%\RAW\ida.log

if /I "%ACTION%"=="inventory" (
  "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_inventory.py %LIBDIR%\RAW" "%SO%"
  exit /b %errorlevel%
)
if /I "%ACTION%"=="bulk" (
  "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_bulk_decompile.py %LIBDIR%\RAW" "%SO%"
  exit /b %errorlevel%
)
if /I "%ACTION%"=="hunt" (
  "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_detection_hunt.py %LIBDIR%\RAW" "%SO%"
  exit /b %errorlevel%
)
if /I "%ACTION%"=="decompile" (
  call :abs %3 OUT
  "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_decompile.py !OUT! %4" "%SO%"
  exit /b %errorlevel%
)
if /I "%ACTION%"=="args" (
  call :abs %3 OUT
  set IDX=%5
  if "!IDX!"=="" set IDX=0
  "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_decoder_args.py !OUT! %4 !IDX!" "%SO%"
  exit /b %errorlevel%
)
if /I "%ACTION%"=="search" (
  call :abs %3 OUT
  set PARAM=%5
  if "!PARAM!"=="" ( "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_search.py !OUT! %4" "%SO%"
  ) else ( "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_search.py !OUT! %4 %PARAM%" "%SO%" )
  exit /b %errorlevel%
)
echo unknown action: %ACTION%
exit /b 2

:abs
set "p=%~1"
set "%~2=%p%"
if "%p:~1,1%"==":" exit /b 0
if "%p:~0,2%"=="\\" exit /b 0
set "%~2=%LIBDIR%\%p%"
exit /b 0
