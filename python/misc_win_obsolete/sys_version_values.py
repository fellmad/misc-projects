import sys

print('Version info:')
print
print('sys.version =', repr(sys.version))
print('sys.version_info =', sys.version_info)
print('sys.hexversion =', hex(sys.hexversion))
print('sys.api_version =', sys.api_version)
print('This interpreter was built for:', sys.platform)
print('Interpreter executable:', sys.executable)
print('Installation prefix   :', sys.prefix)
print('Default encoding    :', sys.getdefaultencoding())
print('Filesystem encoding :', sys.getfilesystemencoding())
