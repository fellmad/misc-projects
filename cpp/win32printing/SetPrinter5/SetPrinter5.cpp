#include "stdafx.h"
#include <WinSpool.h>
#include <atlpath.h>
#include <strstream>
#include <iostream>
#include <vector>
#include "XGetopt.h"

CStringW Win32ErrorString(const long errorCode)
{
    CStringW errorString;
    const DWORD bufsize(512);
    ::FormatMessage(
        FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        errorString.GetBuffer(bufsize),
        bufsize,
        nullptr);
    errorString.ReleaseBuffer();
    errorString.Trim();
    return errorString;
}

CString GetShortExeName()
{
    CStringW exeName;
    ::GetModuleFileNameW(nullptr, exeName.GetBuffer(MAX_PATH), MAX_PATH);
    CPathW shortExeName(exeName);
    shortExeName.StripPath();
    return shortExeName;
}

CStringW DecodePrinterInfo5Attributes(const DWORD attributes)
{
    CStringW msg;
    msg.Format(L"hex: %0X\n", attributes);
    if (attributes & PRINTER_ATTRIBUTE_DEFAULT) msg += L"PRINTER_ATTRIBUTE_DEFAULT\n";
    if (attributes & PRINTER_ATTRIBUTE_DIRECT) msg += L"PRINTER_ATTRIBUTE_DIRECT\n";
    if (attributes & PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST) msg += L"PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST\n";
    if (attributes & PRINTER_ATTRIBUTE_ENABLE_BIDI) msg += L"PRINTER_ATTRIBUTE_ENABLE_BIDI\n";
    if (attributes & PRINTER_ATTRIBUTE_ENABLE_DEVQ) msg += L"PRINTER_ATTRIBUTE_ENABLE_DEVQ\n";
    if (attributes & PRINTER_ATTRIBUTE_FAX) msg += L"PRINTER_ATTRIBUTE_FAX\n";
    if (attributes & PRINTER_ATTRIBUTE_FRIENDLY_NAME) msg += L"PRINTER_ATTRIBUTE_FRIENDLY_NAME\n";
    if (attributes & PRINTER_ATTRIBUTE_HIDDEN) msg += L"PRINTER_ATTRIBUTE_HIDDEN\n";
    if (attributes & PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS) msg += L"PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS\n";
    if (attributes & PRINTER_ATTRIBUTE_LOCAL) msg += L"PRINTER_ATTRIBUTE_LOCAL\n";
    if (attributes & PRINTER_ATTRIBUTE_MACHINE) msg += L"PRINTER_ATTRIBUTE_MACHINE\n";
    if (attributes & PRINTER_ATTRIBUTE_NETWORK) msg += L"PRINTER_ATTRIBUTE_NETWORK\n";
    if (attributes & PRINTER_ATTRIBUTE_PUBLISHED) msg += L"PRINTER_ATTRIBUTE_PUBLISHED\n";
    if (attributes & PRINTER_ATTRIBUTE_PUSHED_MACHINE) msg += L"PRINTER_ATTRIBUTE_PUSHED_MACHINE\n";
    if (attributes & PRINTER_ATTRIBUTE_PUSHED_USER) msg += L"PRINTER_ATTRIBUTE_PUSHED_USER\n";
    if (attributes & PRINTER_ATTRIBUTE_QUEUED) msg += L"PRINTER_ATTRIBUTE_QUEUED\n";
    if (attributes & PRINTER_ATTRIBUTE_RAW_ONLY) msg += L"PRINTER_ATTRIBUTE_RAW_ONLY\n";
    if (attributes & PRINTER_ATTRIBUTE_SHARED) msg += L"PRINTER_ATTRIBUTE_SHARED\n";
    if (attributes & PRINTER_ATTRIBUTE_TS) msg += L"PRINTER_ATTRIBUTE_TS\n";
    if (attributes & PRINTER_ATTRIBUTE_TS_GENERIC_DRIVER) msg += L"PRINTER_ATTRIBUTE_TS_GENERIC_DRIVER\n";
    if (attributes & PRINTER_ATTRIBUTE_WORK_OFFLINE) msg += L"PRINTER_ATTRIBUTE_WORK_OFFLINE\n";
    return msg;
}

void SetPrinterOnline(const HANDLE printerHandle)
{
    DWORD needed {};
    CStringW s;

    int rc = ::GetPrinterW(printerHandle, 2, nullptr, 0, &needed);
    auto lastError = ::GetLastError();
    if (!(0 == rc && ERROR_INSUFFICIENT_BUFFER == lastError)) {
        const auto dw = ::GetLastError();
        s.Format(L"GetPrinterW(): %d", dw);
        throw s;
    }

    std::vector <byte> printerInfo2Bytes(needed);

    DWORD returned {};
    rc = ::GetPrinterW(printerHandle, 2, &printerInfo2Bytes[0], needed, &returned);
    lastError = ::GetLastError();
    if (0 == rc) {
        const auto dw = ::GetLastError();
        s.Format(L"GetPrinterW(): %d", dw);
        throw s;
    }

    const auto printer_info_2 = (PRINTER_INFO_2*) &printerInfo2Bytes[0];
    if (PRINTER_STATUS_OFFLINE & printer_info_2->Status) {
        DWORD newStatus = 0;
        rc = ::SetPrinterW(printerHandle, 0, (PBYTE) newStatus, PRINTER_CONTROL_SET_STATUS);
        if (0 == rc) {
            const auto dw = ::GetLastError();
            s.Format(L"GetPrinterW(): %d", dw);
            throw s;
        }
    }
}

void usage()
{
    std::wcout << std::endl << GetShortExeName().GetBuffer();
    std::wcout << " does print spooler things with the win32 SetPrinter() function -" << std::endl;
    std::wcout << "using the PRINTER_INFO_5 data structure." << std::endl << std::endl;
    std::wcout << "  -n <printername>. Required. Try -n \"XPS Card Printer\"." << std::endl;
    ::exit(-1);
}

int wmain(int argc, WCHAR* argv[])
{
    CStringW s;
    CStringW printerName;

    int c(0);
    while ((c = getopt(argc, argv, L"n:")) != EOF) {
        switch (c) {
        case L'n': printerName = optarg; break;
        default:
            usage();
        }
    }

    if (printerName.IsEmpty()) usage();

    try {
        HANDLE printerHandle {};
        PRINTER_DEFAULTS pd {};
        pd.DesiredAccess = PRINTER_ALL_ACCESS;

        int rc = ::OpenPrinter(printerName.GetBuffer(), &printerHandle, &pd);
        if (!rc) {
            s.Format(L"OpenPrinter(%s): %s", printerName, Win32ErrorString(::GetLastError()));
            throw s;
        }

        // first, get buf size needed for actual call:
        DWORD needed(0);
        rc = ::GetPrinter(printerHandle, 5, nullptr, 0, &needed);
        DWORD dw = ::GetLastError();
        if (ERROR_INSUFFICIENT_BUFFER != dw) {
            s.Format(L"GetPrinter(): expected ERROR_INSUFFICIENT_BUFFER. got %d", dw);
            throw s;
        }

        std::vector <byte> portInfo5byteVector(needed);
        PRINTER_INFO_5* printerInfo5Buf = (PRINTER_INFO_5*) (&portInfo5byteVector[0]);
        rc = ::GetPrinter(printerHandle, 5, (PBYTE) printerInfo5Buf, needed, &needed);
        if (!rc) {
            dw = ::GetLastError();
            s.Format(L"GetPrinter(): %d", dw);
            throw s;
        }

        std::cout << "current printer attributes:" << std::endl;
        std::cout << CT2A(DecodePrinterInfo5Attributes(printerInfo5Buf->Attributes)) << std::endl;

        PRINTER_INFO_5 printerInfo5 = {0};
        printerInfo5.Attributes = printerInfo5Buf->Attributes;
        printerInfo5.pPortName = printerInfo5Buf->pPortName;
        printerInfo5.pPrinterName = printerInfo5Buf->pPrinterName;

        std::cout << "setting printer status to zero:" << std::endl;
        rc = ::SetPrinter(printerHandle, 5, (BYTE*) &printerInfo5, 0);
        if (!rc) {
            s.Format(L"SetPrinter(%s): %s", printerName, Win32ErrorString(::GetLastError()));
            throw s;
        }

        std::cout << "setting printer online:" << std::endl;
        SetPrinterOnline(printerHandle);

        rc = ::ClosePrinter(printerHandle);
    }
    catch (CStringW& s) {
        std::wcerr << s.GetBuffer() << std::endl;
    }

    return 0;
}
