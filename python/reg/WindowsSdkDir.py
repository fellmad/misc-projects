# Windows Registry Editor Version 5.00
# [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Microsoft SDKs\Windows\v10.0]
# "InstallationFolder"="C:\\Program Files (x86)\\Windows Kits\\10\\"
# "ProductName"="Microsoft Windows SDK for Windows 10.0.10240"
# "ProductVersion"="10.0.10240"

import winreg

key = winreg.OpenKey(
    winreg.HKEY_LOCAL_MACHINE,
    r"SOFTWARE\Wow6432Node\Microsoft\Microsoft SDKs\Windows\v10.0",
)
(dummy, valuecount, dummy) = winreg.QueryInfoKey(key)
print(valuecount)
for i in range(0, valuecount):
    print(winreg.EnumValue(key, i))
result = winreg.QueryValueEx(key, "InstallationFolder")
print(result)
