import os
import sys
import subprocess
import argparse

obj_folders = [
    "objchk_wlh_amd64",
    "objchk_wlh_x86",
    "objfre_wlh_amd64",
    "objfre_wlh_x86"
]


def get_candidate_folders(startfolder, verbose=False):
    candidate_folders = []
    for root, dirs, files in os.walk(startfolder):
        for dir in dirs:
            if dir.lower() in obj_folders:
                fqfolder = os.path.join(root, dir)
                candidate_folders.append(fqfolder)
    if verbose:
        print 'candidate folders:'
        for folder in candidate_folders:
            print ' ', folder
    return candidate_folders


def delete_folders(candidate_folders, verbose):
    for folder in candidate_folders:
        cmd = 'cmd /c rd ' + folder + ' /s/q 1>nul 2>nul'
        if verbose:
            print('issuing:', cmd)
        subprocess.call(cmd)


def get_cmd_line_options():
    parser = argparse.ArgumentParser()
    parser.add_argument("-s", "--srcfolder",
                        help="location of the wdk 'src' folder to be cleaned.")
    parser.add_argument("-v", '--verbose',
                        action="store_true",
                        default=False,
                        help="verbose; default=%(default)s.")
    options = parser.parse_args()
    if options.srcfolder is None:
        print '-s or --srcfolder required.'
        sys.exit(-1)
    return options


def delete_log_files(folder, verbose):
    delfileextensions = ['log', 'err', 'wrn']
    for ext in delfileextensions:
        pattern = os.path.join(folder, '*.' + ext)
        cmd = 'cmd /c del ' + pattern + ' /s 1>nul 2>nul'
        if verbose:
            print('issuing:', cmd)
        subprocess.call(cmd)


if __name__ == "__main__":
    options = get_cmd_line_options()
    candidate_folders = get_candidate_folders(
        options.srcfolder,
        options.verbose)
    delete_folders(candidate_folders, options.verbose)
    delete_log_files(options.srcfolder, options.verbose)
