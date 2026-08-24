setlocal

call vs2013env

set pfxFileName=c:\cedar_svn\TNG\TNG\Driver\build\self.signing\certificate\DriverTestCert.pfx
set pfxPassword=drivertest

for %%f in (amd64\*) do (
  signtool.exe sign /v /f %pfxFileName% /p %pfxPassword%^
  /t http://timestamp.verisign.com/scripts/timestamp.dll /du "http://www.datacard.com"^
  "%%f"
)

inf2cat.exe /verbose /driver:"." /os:7_X64,8_X64

signtool.exe sign /v /f %pfxFileName% /p %pfxPassword%^
 /t http://timestamp.verisign.com/scripts/timestamp.dll /du "http://www.datacard.com"^
 ptpcplpr.cat

endlocal