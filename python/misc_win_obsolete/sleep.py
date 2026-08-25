"""
sleep for while.
"""

import argparse
import sys
import time


def parse_sleep_time(time_string):
    """
    for the given time in a string like 'hh:mm:ss', or 'ssssss', return the
    numeric hours, minutes, seconds...and total elapsed seconds.
    """
    hh = 0
    mm = 0
    ss = 0
    flds = time_string.split(":")
    try:
        if len(flds) == 1:
            ss = int(flds[0])
        elif len(flds) == 2:
            mm = int(flds[0])
            ss = int(flds[1])
        elif len(flds) == 3:
            hh = int(flds[0])
            mm = int(flds[1])
            ss = int(flds[2])
        else:
            raise "bad time"
    except ValueError:
        pass
    secs = hh * 3600 + mm * 60 + ss
    return secs


def parse_wait_until_time(time_string):
    """
    for the given time in a string like 'hh:mm:ss', return the numeric hours,
    minutes, seconds...and total elapsed seconds.
    """
    hh = 0
    mm = 0
    ss = 0
    flds = time_string.split(":")
    if len(flds) == 3:
        hh = int(flds[0])
        mm = int(flds[1])
        ss = int(flds[2])
    else:
        raise "bad. need hh:mm:ss."
    curtime = time.time()
    currenttimetuple = time.localtime(curtime)
    untiltimetuple = (
        currenttimetuple[0],
        currenttimetuple[1],
        currenttimetuple[2],
        hh,
        mm,
        ss,
        currenttimetuple[6],
        currenttimetuple[7],
        currenttimetuple[8],
    )
    untilesecs = time.mktime(untiltimetuple)
    untilesecs = max(untilesecs - curtime, 0)
    return untilesecs


def parse_cmd_line_args():
    """
    parse the cmd line args
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("-s", dest="sleepamount", help="format: hh:mm:ss")
    parser.add_argument("-u", dest="sleepuntiltime", help="format: hh:mm:ss")
    options = parser.parse_args()

    if not options.sleepamount and not options.sleepuntiltime:
        parser.print_help()
    return options


if __name__ == "__main__":
    OPTIONS = parse_cmd_line_args()
    if OPTIONS.sleepamount:
        secs = parse_sleep_time(OPTIONS.sleepamount)
        localtime = time.localtime()
        starttime = time.strftime("%Y %H:%M:%S", localtime)
        msg = str.format("{} sleeping {} secs...", starttime, secs)
        print(msg)
        time.sleep(secs)
        localtime = time.localtime()
        endtime = time.strftime("%Y %H:%M:%S", localtime)
        print(endtime)
    elif OPTIONS.sleepuntiltime:
        secs = parse_wait_until_time(OPTIONS.sleepuntiltime)
        localtime = time.localtime()
        starttime = time.strftime("%Y %H:%M:%S", localtime)
        msg = str.format("{} sleeping {} secs...", starttime, secs)
        print(msg)
        time.sleep(secs)
        localtime = time.localtime()
        endtime = time.strftime("%Y %H:%M:%S", localtime)
        print(endtime)
