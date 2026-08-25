from pprint import pprint
import os


def environ_after(cmd):
    cmd += " >nul && set"
    env = {}
    for l in os.popen(cmd).readlines():
        key, val = l.split("=", 2)
        env[key.strip().upper()] = val.strip()
    return env


def compare_dicts(dict1, dict2):
    keys1 = set(dict1.keys())
    keys2 = set(dict2.keys())
    only_in_1 = list(keys1-keys2)
    only_in_2 = list(keys2-keys1)
    changed = [k for k in keys1.intersection(keys2) if dict1[k] !=
               dict2[k]]
    return only_in_1, only_in_2, changed


cur_env = os.environ
new_env = environ_after(
    r'"E: \tools\WinDDK\7000.0.winmain_win7beta.081212-1400\bin\setenv.bat E: \tools\WinDDK\7000.0.winmain_win7beta.081212-1400 chk x86 WLH"')
removed_vars, new_vars, changed_vars = compare_dicts(cur_env, new_env)
print "removed:"
pprint(removed_vars)
print
print "added:"
pprint(new_vars)
print
print "changed:"
for k in changed_vars:
    print k
    print "   before:", cur_env[k]
    print "   after: ", new_env[k]
