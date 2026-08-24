#include "stdafx.h"
#include <atlfile.h>
#include <iostream>
#include <vector>
#include <atlpath.h>
#include "XGetopt.h"

using namespace std;

void usage(CString longExeName)
{
    CPath shortExeName(longExeName);
    shortExeName.StripPath();
    shortExeName.RemoveExtension();

    cout << endl;
    cout << "usage: " << CT2A(shortExeName) << " <options>" << endl;
    cout << "  " << "-p <printername>. required." << endl;
    cout << "  " << "-f <xps filename>. required." << endl;
    cout << endl;
    exit(0);
}

CString StringFromError(const long lrc)
{
    CString errorString;
    const UINT uiSize = 512;
    TCHAR pszMsg[uiSize] = {0};
    DWORD dwSize = ::FormatMessage(
        FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        lrc,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        pszMsg,
        uiSize,
        NULL);
    if (dwSize > 2) {
        // Take out the trailing CRLF.
        pszMsg[--dwSize] = 0;
        pszMsg[--dwSize] = 0;
    }
    errorString = pszMsg;
    return errorString;
}

int _tmain(int argc, _TCHAR* argv[])
{
    DWORD dw(0);
    HANDLE printerHandle(0);

    CString printerName;
    CString xpsFileName;

    int c(0);
    while ((c = getopt(argc, argv, _T("p:f:"))) != EOF) {
        switch (c) {
        case TEXT('p'):
            printerName = optarg;
            break;

        case TEXT('f'):
            xpsFileName = optarg;
            break;

        default:
            usage(argv[0]);
        }
    }

    if (printerName.IsEmpty()) {
        usage(argv[0]);
    }

    if (xpsFileName.IsEmpty()) {
        usage(argv[0]);
    }

    // open the input xps file and read it into memory:
    CAtlFile inputXpsFile;
    int rc = inputXpsFile.Create(xpsFileName, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);
    if (FAILED(rc)) {
        wcout << L"opening " << xpsFileName.GetBuffer() << " err: " << hex << rc << " " << StringFromError(rc).GetBuffer() << endl;
        ::exit(-1);
    }

    ULONGLONG inputXpsFileSize = {0};
    rc = inputXpsFile.GetSize(inputXpsFileSize);
    if (FAILED(rc)) {
        wcout << L"GetSize()" << xpsFileName.GetBuffer() << " err: " << hex << rc << " " << StringFromError(rc).GetBuffer() << endl;
        ::exit(-1);
    }

    vector <byte> fileBuffer((int) inputXpsFileSize);
    rc = inputXpsFile.Read(&fileBuffer[0], (int) inputXpsFileSize);
    if (FAILED(rc)) {
        wcout << L"Read(): " << "win32 error: " << rc << " " << StringFromError(rc).GetBuffer() << endl;
        ::exit(-1);
    }
    inputXpsFile.Close();

    rc = ::OpenPrinter(printerName.GetBuffer(0), &printerHandle, NULL);
    if (0 == rc) {
        dw = ::GetLastError();
        wcout << L"OpenPrinter(): " << printerName.GetBuffer(0) << " " << dw << " " << StringFromError(dw).GetBuffer() << endl;
        ::exit(-1);
    }

    // get 'needed' bytecount for goofy ADDJOB_INFO_1 structure. we expect err 122
    DWORD needed(0);
    rc = ::AddJob(printerHandle, 1, NULL, 0, &needed);
    if (ERROR_INSUFFICIENT_BUFFER == rc) {
        dw = ::GetLastError();
        wcout << L"AddJob(): " << "win32 error: " << dw << endl;
        ::exit(-1);
    }

    vector <byte> jobInfo1Buf(needed, 0);
    ADDJOB_INFO_1* pAddJobInfo1 = (ADDJOB_INFO_1*) &jobInfo1Buf[0];

    // this gives us a spool filename and a jobID:
    rc = ::AddJob(printerHandle, 1, (PBYTE) pAddJobInfo1, needed, &needed);
    if (0 == rc) {
        dw = ::GetLastError();
        wcout << L"AddJob(): " << "win32 error: " << dw << endl;
        ::exit(-1);
    }

    cout << "spool filename: " << CT2A(pAddJobInfo1->Path) << endl;
    cout << "jobID: " << pAddJobInfo1->JobId << endl;

    const CString spoolFileName = pAddJobInfo1->Path;
    const DWORD jobID = pAddJobInfo1->JobId;

    // copy the contents of the input xps file to the spoolfile:
    CAtlFile spoolFile;
    rc = spoolFile.Create(spoolFileName, GENERIC_WRITE, FILE_SHARE_WRITE, CREATE_NEW);
    if (FAILED(rc)) {
        wcout << L"Create(): " << "win32 error: " << rc << endl;
        ::exit(-1);
    }

    rc = spoolFile.Write(&fileBuffer[0], (int) inputXpsFileSize);
    if (FAILED(rc)) {
        wcout << L"Write(): " << "win32 error: " << rc << endl;
        ::exit(-1);
    }
    spoolFile.Close();

    rc = ::ScheduleJob(printerHandle, jobID);
    if (0 == rc) {
        dw = ::GetLastError();
        wcout << L"ScheduleJob(): " << "win32 error: " << dw << endl;
        ::exit(-1);
    }

    rc = ::ClosePrinter(printerHandle);
    if (0 == rc) {
        dw = ::GetLastError();
        wcout << L"ClosePrinter(): " << "win32 error: " << dw << endl;
        ::exit(-1);
    }

    return 0;
}