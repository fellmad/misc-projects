import os
import glob
import sys


def quote(s):
    return '"' + s + '"'


def usage(args):
    s = os.path.splitext(os.path.basename(args[0]))[0]
    print('usage:', s, '*.cpp *.h ... do cmd parm1 parm2 ...')


def getdopos(args):
    dopos = 0
    pos = 0
    for arg in args:
        if arg.lower() == 'do':
            dopos = pos
            break
        else:
            pos += 1
    # 'do' must be present on our cmd-line, and cannot be the first or last parm:
    if dopos == len(args) - 1:
        dopos = 0
    return dopos


def doargs(args):
    dopos = getdopos(args)
    if dopos:
        globbers = []
        for pos in range(dopos):
            globbers.append(args[pos])
        files = []
        for globber in globbers:
            files += glob.glob(globber)
        for file in files:
            cmd = args[dopos + 1] + ' ' + quote(file)
            for pos in range(dopos + 2, len(args)):
                cmd += ' ' + args[pos]
            os.system(cmd)
    else:
        usage(args)


if __name__ == '__main__':
    args = sys.argv
    if len(args) > 3:
        args = sys.argv[1:]
        doargs(args)
    else:
        usage(args)
