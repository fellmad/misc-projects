#include "stdafx.h"
#include <WinSpool.h>
#include <atlpath.h>
#include <iostream>
#include "XGetopt.h"

using namespace std;

CString Win32ErrorString(const long errorCode)
{
    CString errorString;
    const DWORD bufsize(512);
    ::FormatMessage(
        FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        errorString.GetBuffer(bufsize),
        bufsize,
        NULL);
    errorString.ReleaseBuffer();
    errorString.Trim();
    return errorString;
}

CString GetShortExeName()
{
    CString exeName;
    ::GetModuleFileName(NULL, exeName.GetBuffer(MAX_PATH), MAX_PATH);
    CPath shortExeName(exeName);
    shortExeName.StripPath();
    return shortExeName;
}

void usage()
{
    cout << endl << CT2A(GetShortExeName()) << " does print spooler things using the win32 SetPrinter() function." << endl << endl;
    cout << CT2A(GetShortExeName()) << " -n <printername> -c <command>" << endl;
    cout << "  -n <printername>. Required. Try -n \"XPS Card Printer\"." << endl;
    cout << "  -c <command>. Required. One of 'pause', 'purge', 'resume', 'set_status'" << endl << endl;
    ::exit(-1);
}

int _tmain(int argc, _TCHAR* argv[])
{
    CString  s;
    CString  commandString;
    CString  printerName;
    DWORD    command(0);

    int c(0);
    while ((c = getopt(argc, argv, _T("n:c:"))) != EOF) {
        switch (c) {
        case L'n': printerName = optarg; break;
        case L'c': commandString = optarg; commandString = commandString.MakeLower(); break;
        default:
            usage();
        }
    }

    if (printerName.IsEmpty()) usage();
    if (commandString.IsEmpty()) usage();

    if ("purge" == commandString) {
        command = PRINTER_CONTROL_PURGE;
    }
    else if ("pause" == commandString) {
        command = PRINTER_CONTROL_PAUSE;
    }
    else if ("resume" == commandString) {
        command = PRINTER_CONTROL_RESUME;
    }
    else if ("set_status" == commandString) {
        cout << "sorry; set_status not working yet." << endl; ::exit(-1);
    }
    else {
        usage();
    }

    try {
        HANDLE printerHandle = {0};

        PRINTER_DEFAULTS pd = {0};
        pd.DesiredAccess = PRINTER_ALL_ACCESS;

        int rc = ::OpenPrinter(printerName.GetBuffer(), &printerHandle, &pd);
        if (!rc) {
            s.Format(L"OpenPrinter(%s): %s", printerName, Win32ErrorString(::GetLastError()));
            throw s;
        }

        rc = ::SetPrinter(printerHandle, 0, NULL, command);
        if (!rc) {
            s.Format(L"SetPrinter(%s): %s", printerName, Win32ErrorString(::GetLastError()));
            throw s;
        }

        rc = ::ClosePrinter(printerHandle);
    }
    catch (CString& s) {
        wcerr << s.GetBuffer() << endl;
    }

    return 0;
}