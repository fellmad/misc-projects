import time


def get_current_time_yyyymmdd():
    format = '%Y.%m.%d.%H.%M.%S'
    return time.strftime(format, time.localtime(time.time()))


if __name__ == '__main__':
    print(get_current_time_yyyymmdd())
