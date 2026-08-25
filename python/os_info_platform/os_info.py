# https://www.ostechnix.com/find-linux-system-details-using-python/

import platform

print('Machine :', platform.machine())
print('Node :', platform.node())
print('Platform :', platform.platform())
print('Processor :', platform.processor())
print('Release :', platform.release())
print('System :', platform.system())
print('Uname:', platform.uname())
print('Version :', platform.version())
print('win32_edition()', platform.win32_edition())
print('Win32_ver', platform.win32_ver())
