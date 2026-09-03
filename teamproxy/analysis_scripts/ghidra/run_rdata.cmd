@echo off
cd /d E:\android_version\LIXCLIENT_version2\teamproxy
set GHIDRA_RDATA_USERS=E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out\rdata_users.txt
call "E:\android_version\LIXCLIENT_version2\TOOLS\ghidra_12.1.3_PUBLIC\support\analyzeHeadless.bat" E:\android_version\LIXCLIENT_version2\teamproxy\ghidra_out ghidra_lib123 -process lib123.so -noanalysis -scriptPath analysis_scripts\ghidra -postScript TraceRdataUsers.java
echo EXITCODE=%ERRORLEVEL%
