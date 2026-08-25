# see: https://github.com/mhammond/pywin32    and    https://pypi.org/project/pywin32/
# install pywin32 via pip:
# pip install pywin32

import pywintypes
import win32api

print(win32api.SearchPath(None, "cmd.exe"))
print(win32api.SearchPath(None, "python.exe"))
print(win32api.SearchPath(None, "py.exe"))
print(win32api.SearchPath(None, "where.exe"))

try:
    filename = "junk.12345"
    print(win32api.SearchPath(None, filename))
except pywintypes.error as ex:
    print('fail: ', filename, ex)
try:
    filename = "cl.exe"
    print(win32api.SearchPath(None, filename))
except pywintypes.error as ex:
    print('fail: ', filename, ex)
