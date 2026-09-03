@echo off
cd /d E:\android_version\LIXCLIENT_version2\teamproxy
set GHIDRA_DUMP_PATH=E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\lib123_arm64_decomp.c
call "E:\android_version\LIXCLIENT_version2\TOOLS\ghidra_12.1.3_PUBLIC\support\analyzeHeadless.bat" E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out ghidra_lib123 -import decompiled\lib\arm64-v8a\lib123.so -scriptPath analysis_scripts\ghidra -postScript DumpAllFunctions.java
echo EXITCODE=%ERRORLEVEL%
