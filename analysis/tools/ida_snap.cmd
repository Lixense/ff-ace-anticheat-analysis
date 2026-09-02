@echo off
rem ida_snap.cmd — per-agent SNAPSHOT wrapper so many agents query the SAME lib concurrently.
rem IDA locks the .i64 next to the .so (error code 4 on 2nd opener). A COPY opens independently.
rem   analysis\tools\ida_snap.cmd <snapid> <lib> <action> [args...]
rem   snapid : unique tag per agent (e.g. a1, b4) -> analysis\_snap\<snapid>\
rem   lib    : libanogs | libanort | libmain
rem   action : hunt | decompile <out> <targets> | args <out> <decoder> [idx] | search <out> <mode> [param]
rem Outputs land under analysis\_snap\<snapid>\RAW\ (or absolute <out>).
setlocal EnableDelayedExpansion
rem Point ROOT at the repo root (where analysis\ sits), and IDAT at your idat.exe.
rem Override by setting the env vars before calling, e.g.  set ROOT=D:\work\ff-ace  &  set IDAT=...
if not defined ROOT set ROOT=%~dp0..\..
if not defined IDAT set IDAT=C:\Program Files\IDA Professional 9.4\idat.exe
set TOOLS=%ROOT%\analysis\tools

set SNAPID=%1
set LIB=%2
set ACTION=%3
if "%SNAPID%"=="" echo ERROR: snapid required & exit /b 2
if "%LIB%"=="" echo ERROR: lib: libanogs^|libanort^|libmain & exit /b 2
if "%ACTION%"=="" echo ERROR: action required & exit /b 2

set SRCDIR=%ROOT%\analysis\%LIB%
set SRCSO=%SRCDIR%\%LIB%.so
set SRCI64=%SRCDIR%\%LIB%.so.i64
if not exist "%SRCI64%" echo ERROR: %SRCI64% not found & exit /b 2

set SNAPDIR=%ROOT%\analysis\_snap\%SNAPID%
set SO=%SNAPDIR%\%LIB%.so
if not exist "%SNAPDIR%\RAW" mkdir "%SNAPDIR%\RAW" 2>nul
rem copy .so + .i64 ONCE (idempotent). /Y overwrite off if present.
if not exist "%SO%" copy /Y "%SRCSO%" "%SO%" >nul
if not exist "%SNAPDIR%\%LIB%.so.i64" copy /Y "%SRCI64%" "%SNAPDIR%\%LIB%.so.i64" >nul

set LOG=%SNAPDIR%\RAW\ida.log

if /I "%ACTION%"=="hunt" (
  "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_detection_hunt.py %SNAPDIR%\RAW" "%SO%"
  exit /b %errorlevel%
)
if /I "%ACTION%"=="decompile" (
  call :abs %4 OUT
  "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_decompile.py !OUT! %5" "%SO%"
  exit /b %errorlevel%
)
if /I "%ACTION%"=="args" (
  call :abs %4 OUT
  set IDX=%6
  if "!IDX!"=="" set IDX=0
  "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_decoder_args.py !OUT! %5 !IDX!" "%SO%"
  exit /b %errorlevel%
)
if /I "%ACTION%"=="search" (
  call :abs %4 OUT
  set PARAM=%6
  if "!PARAM!"=="" ( "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_search.py !OUT! %5" "%SO%"
  ) else ( "%IDAT%" -A -L"%LOG%" -S"%TOOLS%\ida_search.py !OUT! %5 !PARAM!" "%SO%" )
  exit /b %errorlevel%
)
echo unknown action: %ACTION%
exit /b 2

:abs
set "p=%~1"
set "%~2=%p%"
if "%p:~1,1%"==":" exit /b 0
if "%p:~0,2%"=="\\" exit /b 0
set "%~2=%SNAPDIR%\%p%"
exit /b 0
