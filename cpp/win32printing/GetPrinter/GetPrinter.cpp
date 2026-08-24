#include "targetver.h"
#include <Windows.h>
#include <WinSpool.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>

inline std::wstring trim(const std::wstring &s)
{
    auto wsfront = std::find_if_not(s.begin(), s.end(), [] (int c) {return std::isspace(c); });
    auto wsback = std::find_if_not(s.rbegin(), s.rend(), [] (int c) {return std::isspace(c); }).base();
    const auto result = (wsback <= wsfront ? std::wstring() : std::wstring(wsfront, wsback));
    return result;
}

std::wstring GetWin32ErrString(const DWORD rc)
{
    const UINT maxMessageLength {1024};
    WCHAR message[maxMessageLength] {};
    const DWORD formatMessageResult = ::FormatMessageW(
        FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr,
        rc,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        message,
        1024,
        nullptr);
    std::wstring result = message;

    if (!formatMessageResult) {
        std::wcerr << "FormatMessageW() fail: " << formatMessageResult << std::endl;
    }

    result = trim(result);
    return result;
}

struct PrinterInfo1 {
    DWORD flags;
    std::wstring description;
    std::wstring name;
    std::wstring comment;
};

struct PrinterInfo2 {
    DWORD Attributes;
    DWORD AveragePPM;
    DWORD cJobs;
    DWORD DefaultPriority;
    DWORD Priority;
    DWORD StartTime;
    DWORD Status;
    DWORD UntilTime;
    LPDEVMODEW pDevMode;
    PSECURITY_DESCRIPTOR pSecurityDescriptor;
    std::wstring Comment;
    std::wstring Datatype;
    std::wstring DriverName;
    std::wstring Location;
    std::wstring Parameters;
    std::wstring PortName;
    std::wstring PrinterName;
    std::wstring PrintProcessor;
    std::wstring SepFile;
    std::wstring ServerName;
    std::wstring ShareName;
};

struct PrinterInfo5 {
    std::wstring PrinterName;
    std::wstring PortName;
    DWORD Attributes;
    DWORD DeviceNotSelectedTimeout;
    DWORD TransmissionRetryTimeout;
};

std::wstring PrinterStatusToString(const DWORD status)
{
    std::wstring result;
    result += (status & PRINTER_STATUS_PAUSED) ? L"PRINTER_STATUS_PAUSED " : L"";
    result += (status & PRINTER_STATUS_ERROR) ? L"PRINTER_STATUS_ERROR " : L"";
    result += (status & PRINTER_STATUS_PENDING_DELETION) ? L"PRINTER_STATUS_PENDING_DELETION " : L"";
    result += (status & PRINTER_STATUS_PAPER_JAM) ? L"PRINTER_STATUS_PAPER_JAM " : L"";
    result += (status & PRINTER_STATUS_PAPER_OUT) ? L"PRINTER_STATUS_PAPER_OUT " : L"";
    result += (status & PRINTER_STATUS_MANUAL_FEED) ? L"PRINTER_STATUS_MANUAL_FEED " : L"";
    result += (status & PRINTER_STATUS_PAPER_PROBLEM) ? L"PRINTER_STATUS_PAPER_PROBLEM " : L"";
    result += (status & PRINTER_STATUS_OFFLINE) ? L"PRINTER_STATUS_OFFLINE " : L"";
    result += (status & PRINTER_STATUS_IO_ACTIVE) ? L"PRINTER_STATUS_IO_ACTIVE " : L"";
    result += (status & PRINTER_STATUS_BUSY) ? L"PRINTER_STATUS_BUSY " : L"";
    result += (status & PRINTER_STATUS_PRINTING) ? L"PRINTER_STATUS_PRINTING " : L"";
    result += (status & PRINTER_STATUS_OUTPUT_BIN_FULL) ? L"PRINTER_STATUS_OUTPUT_BIN_FULL " : L"";
    result += (status & PRINTER_STATUS_NOT_AVAILABLE) ? L"PRINTER_STATUS_NOT_AVAILABLE " : L"";
    result += (status & PRINTER_STATUS_WAITING) ? L"PRINTER_STATUS_WAITING " : L"";
    result += (status & PRINTER_STATUS_PROCESSING) ? L"PRINTER_STATUS_PROCESSING " : L"";
    result += (status & PRINTER_STATUS_INITIALIZING) ? L"PRINTER_STATUS_INITIALIZING " : L"";
    result += (status & PRINTER_STATUS_WARMING_UP) ? L"PRINTER_STATUS_WARMING_UP " : L"";
    result += (status & PRINTER_STATUS_TONER_LOW) ? L"PRINTER_STATUS_TONER_LOW " : L"";
    result += (status & PRINTER_STATUS_NO_TONER) ? L"PRINTER_STATUS_NO_TONER " : L"";
    result += (status & PRINTER_STATUS_PAGE_PUNT) ? L"PRINTER_STATUS_PAGE_PUNT " : L"";
    result += (status & PRINTER_STATUS_USER_INTERVENTION) ? L"PRINTER_STATUS_USER_INTERVENTION " : L"";
    result += (status & PRINTER_STATUS_OUT_OF_MEMORY) ? L"PRINTER_STATUS_OUT_OF_MEMORY " : L"";
    result += (status & PRINTER_STATUS_DOOR_OPEN) ? L"PRINTER_STATUS_DOOR_OPEN " : L"";
    result += (status & PRINTER_STATUS_SERVER_UNKNOWN) ? L"PRINTER_STATUS_SERVER_UNKNOWN " : L"";
    result += (status & PRINTER_STATUS_POWER_SAVE) ? L"PRINTER_STATUS_POWER_SAVE " : L"";
    result += (status & PRINTER_STATUS_SERVER_OFFLINE) ? L"PRINTER_STATUS_SERVER_OFFLINE " : L"";
    result += (status & PRINTER_STATUS_DRIVER_UPDATE_NEEDED) ? L"PRINTER_STATUS_DRIVER_UPDATE_NEEDED" : L"";
    result = trim(result);
    return result;
}

std::wstring PrinterAttributesToString(const DWORD& attributes)
{
    std::wstring result;
    result += (attributes & PRINTER_ATTRIBUTE_DEFAULT) ? L"PRINTER_ATTRIBUTE_DEFAULT " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_DEFAULT) ? L"PRINTER_ATTRIBUTE_DEFAULT " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_DIRECT) ? L"PRINTER_ATTRIBUTE_DIRECT " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST) ? L"PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_ENABLE_BIDI) ? L"PRINTER_ATTRIBUTE_ENABLE_BIDI " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_ENABLE_DEVQ) ? L"PRINTER_ATTRIBUTE_ENABLE_DEVQ " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_FAX) ? L"PRINTER_ATTRIBUTE_FAX " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_FRIENDLY_NAME) ? L"PRINTER_ATTRIBUTE_FRIENDLY_NAME " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_HIDDEN) ? L"PRINTER_ATTRIBUTE_HIDDEN " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS) ? L"PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_LOCAL) ? L"PRINTER_ATTRIBUTE_LOCAL " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_MACHINE) ? L"PRINTER_ATTRIBUTE_MACHINE " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_NETWORK) ? L"PRINTER_ATTRIBUTE_NETWORK " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_PUBLISHED) ? L"PRINTER_ATTRIBUTE_PUBLISHED " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_PUSHED_MACHINE) ? L"PRINTER_ATTRIBUTE_PUSHED_MACHINE " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_PUSHED_USER) ? L"PRINTER_ATTRIBUTE_PUSHED_USER " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_QUEUED) ? L"PRINTER_ATTRIBUTE_QUEUED " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_RAW_ONLY) ? L"PRINTER_ATTRIBUTE_RAW_ONLY " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_SHARED) ? L"PRINTER_ATTRIBUTE_SHARED " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_TS) ? L"PRINTER_ATTRIBUTE_TS " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_TS_GENERIC_DRIVER) ? L"PRINTER_ATTRIBUTE_TS_GENERIC_DRIVER " : L"";
    result += (attributes & PRINTER_ATTRIBUTE_WORK_OFFLINE) ? L"PRINTER_ATTRIBUTE_WORK_OFFLINE " : L"";
    result = trim(result);
    return result;
}

std::wstring PrinterInfo1FlagsToString(const DWORD& flags)
{
    std::wstring result;
    result += (flags & PRINTER_ENUM_DEFAULT) ? L"PRINTER_ENUM_DEFAULT " : L"";
    result += (flags & PRINTER_ENUM_LOCAL) ? L"PRINTER_ENUM_LOCAL " : L"";
    result += (flags & PRINTER_ENUM_CONNECTIONS) ? L"PRINTER_ENUM_CONNECTIONS " : L"";
    result += (flags & PRINTER_ENUM_FAVORITE) ? L"PRINTER_ENUM_FAVORITE " : L"";
    result += (flags & PRINTER_ENUM_NAME) ? L"PRINTER_ENUM_NAME " : L"";
    result += (flags & PRINTER_ENUM_REMOTE) ? L"PRINTER_ENUM_REMOTE " : L"";
    result += (flags & PRINTER_ENUM_SHARED) ? L"PRINTER_ENUM_SHARED " : L"";
    result += (flags & PRINTER_ENUM_NETWORK) ? L"PRINTER_ENUM_NETWORK " : L"";
    result += (flags & PRINTER_ENUM_EXPAND) ? L"PRINTER_ENUM_EXPAND " : L"";
    result += (flags & PRINTER_ENUM_CONTAINER) ? L"PRINTER_ENUM_CONTAINER " : L"";
    result += (flags & PRINTER_ENUM_ICON1) ? L"PRINTER_ENUM_ICON1 " : L"";
    result += (flags & PRINTER_ENUM_ICON2) ? L"PRINTER_ENUM_ICON2 " : L"";
    result += (flags & PRINTER_ENUM_ICON3) ? L"PRINTER_ENUM_ICON3 " : L"";
    result += (flags & PRINTER_ENUM_ICON4) ? L"PRINTER_ENUM_ICON4 " : L"";
    result += (flags & PRINTER_ENUM_ICON5) ? L"PRINTER_ENUM_ICON5 " : L"";
    result += (flags & PRINTER_ENUM_ICON6) ? L"PRINTER_ENUM_ICON6 " : L"";
    result += (flags & PRINTER_ENUM_ICON7) ? L"PRINTER_ENUM_ICON7 " : L"";
    result += (flags & PRINTER_ENUM_ICON8) ? L"PRINTER_ENUM_ICON8 " : L"";
    result += (flags & PRINTER_ENUM_HIDE) ? L"PRINTER_ENUM_HIDE " : L"";
    result += (flags & PRINTER_ENUM_CATEGORY_ALL) ? L"PRINTER_ENUM_CATEGORY_ALL " : L"";
    result += (flags & PRINTER_ENUM_CATEGORY_3D) ? L"PRINTER_ENUM_CATEGORY_3D " : L"";
    result = trim(result);
    return result;
}

std::wstring PrinterInfo1ToString(const PrinterInfo1& printerInfo1)
{
    std::wostringstream ostr;
    ostr << "PRINTER_INFO_1:" << std::endl;
    ostr << "  comment:     " << printerInfo1.comment << std::endl;
    ostr << "  description: " << printerInfo1.description << std::endl;
    ostr << "  name:        " << printerInfo1.name << std::endl;
    ostr << "  flags:       " << std::hex << printerInfo1.flags << std::endl;
    const auto flagsString = PrinterInfo1FlagsToString(printerInfo1.flags);
    ostr << "               " << std::hex << flagsString << std::endl;
    const std::wstring result(ostr.str());
    return result;
}

PrinterInfo1 GetPrinterInfo1(const HANDLE& printerHandle)
{
    DWORD needed {};
    int rc = ::GetPrinterW(printerHandle, 1, nullptr, 0, &needed);
    auto lastError = ::GetLastError();
    if (!(0 == rc && ERROR_INSUFFICIENT_BUFFER == lastError)) {
        std::wcerr << "GetPrinterW() fail: " << lastError << " " << GetWin32ErrString(lastError) << std::endl;
        std::exit(-1);
    }

    std::vector <byte> printerInfo1Bytes(needed);

    DWORD returned {};
    rc = ::GetPrinterW(printerHandle, 1, &printerInfo1Bytes[0], needed, &returned);
    lastError = ::GetLastError();
    if (0 == rc) {
        std::wcerr << "GetPrinterW() fail: " << lastError << " " << GetWin32ErrString(lastError) << std::endl;
        std::exit(-1);
    }

    const auto printer_info_1 = (PRINTER_INFO_1*) &printerInfo1Bytes[0];

    PrinterInfo1 printerInfo1 {};
    printerInfo1.comment = printer_info_1->pComment ? printer_info_1->pComment : L"";
    printerInfo1.description = printer_info_1->pDescription ? printer_info_1->pDescription : L"";
    printerInfo1.flags = printer_info_1->Flags;
    printerInfo1.name = printer_info_1->pName ? printer_info_1->pName : L"";

    return printerInfo1;
}

PrinterInfo2 GetPrinterInfo2(const HANDLE& printerHandle)
{
    DWORD needed {};
    int rc = ::GetPrinterW(printerHandle, 2, nullptr, 0, &needed);
    auto lastError = ::GetLastError();
    if (!(0 == rc && ERROR_INSUFFICIENT_BUFFER == lastError)) {
        std::wcerr << "GetPrinterW() fail: " << lastError << " " << GetWin32ErrString(lastError) << std::endl;
        std::exit(-1);
    }

    std::vector <byte> printerInfo2Bytes(needed);

    DWORD returned {};
    rc = ::GetPrinterW(printerHandle, 2, &printerInfo2Bytes[0], needed, &returned);
    lastError = ::GetLastError();
    if (0 == rc) {
        std::wcerr << "GetPrinterW() fail: " << lastError << " " << GetWin32ErrString(lastError) << std::endl;
        std::exit(-1);
    }

    const auto printer_info_2 = (PRINTER_INFO_2*) &printerInfo2Bytes[0];

    PrinterInfo2 printerInfo2 {};

    printerInfo2.Attributes = printer_info_2->Attributes;
    printerInfo2.AveragePPM = printer_info_2->AveragePPM;
    printerInfo2.cJobs = printer_info_2->cJobs;
    printerInfo2.Comment = printer_info_2->pComment ? printer_info_2->pComment : L"";
    printerInfo2.Datatype = printer_info_2->pDatatype ? printer_info_2->pDatatype : L"";
    printerInfo2.DefaultPriority = printer_info_2->DefaultPriority;
    printerInfo2.DriverName = printer_info_2->pDriverName ? printer_info_2->pDriverName : L"";
    printerInfo2.Location = printer_info_2->pLocation ? printer_info_2->pLocation : L"";
    printerInfo2.Parameters = printer_info_2->pParameters ? printer_info_2->pParameters : L"";
    printerInfo2.pDevMode = printer_info_2->pDevMode;
    printerInfo2.PortName = printer_info_2->pPortName ? printer_info_2->pPortName : L"";
    printerInfo2.PrinterName = printer_info_2->pPrinterName ? printer_info_2->pPrinterName : L"";
    printerInfo2.PrintProcessor = printer_info_2->pPrintProcessor ? printer_info_2->pPrintProcessor : L"";
    printerInfo2.Priority = printer_info_2->Priority;
    printerInfo2.pSecurityDescriptor = printer_info_2->pSecurityDescriptor;
    printerInfo2.SepFile = printer_info_2->pSepFile ? printer_info_2->pSepFile : L"";
    printerInfo2.ServerName = printer_info_2->pServerName ? printer_info_2->pServerName : L"";
    printerInfo2.ShareName = printer_info_2->pShareName ? printer_info_2->pShareName : L"";
    printerInfo2.StartTime = printer_info_2->StartTime;
    printerInfo2.Status = printer_info_2->Status;
    printerInfo2.UntilTime = printer_info_2->UntilTime;
    return printerInfo2;
}

std::wstring PrinterInfo2ToString(const  PrinterInfo2& printerInfo2)
{
    std::wostringstream ostr;
    ostr << "PRINTER_INFO_2" << std::endl;
    ostr << "  Attributes:      " << printerInfo2.Attributes << std::endl;
    auto attribbutesString = PrinterAttributesToString(printerInfo2.Attributes);
    ostr << "  " << attribbutesString << std::endl;
    ostr << "  AveragePPM:      " << printerInfo2.AveragePPM << std::endl;
    ostr << "  cJobs:           " << printerInfo2.cJobs << std::endl;
    ostr << "  Comment:         " << printerInfo2.Comment << std::endl;
    ostr << "  Datatype:        " << printerInfo2.Datatype << std::endl;
    ostr << "  DefaultPriority: " << printerInfo2.DefaultPriority << std::endl;
    ostr << "  DriverName:      " << printerInfo2.DriverName << std::endl;
    ostr << "  Location:        " << printerInfo2.Location << std::endl;
    ostr << "  Parameters:      " << printerInfo2.Parameters << std::endl;
    ostr << "  PortName:        " << printerInfo2.PortName << std::endl;
    ostr << "  PrinterName:     " << printerInfo2.PrinterName << std::endl;
    ostr << "  PrintProcessor:  " << printerInfo2.PrintProcessor << std::endl;
    ostr << "  Priority:        " << printerInfo2.Priority << std::endl;
    ostr << "  SepFile:         " << printerInfo2.SepFile << std::endl;
    ostr << "  ServerName:      " << printerInfo2.ServerName << std::endl;
    ostr << "  ShareName:       " << printerInfo2.ShareName << std::endl;
    ostr << "  StartTime:       " << printerInfo2.StartTime << std::endl;
    ostr << "  Status:          " << printerInfo2.Status << std::endl;
    if (printerInfo2.Status)
        ostr << "  " << PrinterStatusToString(printerInfo2.Status) << std::endl;
    ostr << "  UntilTime:       " << printerInfo2.UntilTime << std::endl;

    // dlftodo:
    //LPDEVMODEW pDevMode;
    //PSECURITY_DESCRIPTOR pSecurityDescriptor;

    const std::wstring result(ostr.str());
    return result;
}

PrinterInfo5 GetPrinterInfo5(const HANDLE& printerHandle)
{
    DWORD needed {};
    int rc = ::GetPrinterW(printerHandle, 5, nullptr, 0, &needed);
    auto lastError = ::GetLastError();
    if (!(0 == rc && ERROR_INSUFFICIENT_BUFFER == lastError)) {
        std::wcerr << "GetPrinterW() fail: " << lastError << " " << GetWin32ErrString(lastError) << std::endl;
        std::exit(-1);
    }

    std::vector <byte> printerInfo5Bytes(needed);

    DWORD returned {};
    rc = ::GetPrinterW(printerHandle, 5, &printerInfo5Bytes[0], needed, &returned);
    lastError = ::GetLastError();
    if (0 == rc) {
        std::wcerr << "GetPrinterW() fail: " << lastError << " " << GetWin32ErrString(lastError) << std::endl;
        std::exit(-1);
    }

    const auto printer_info_5 = (PRINTER_INFO_5*) &printerInfo5Bytes[0];

    PrinterInfo5 printerInfo5 {};

    printerInfo5.Attributes = printer_info_5->Attributes;
    printerInfo5.DeviceNotSelectedTimeout = printer_info_5->DeviceNotSelectedTimeout;
    printerInfo5.PortName = printer_info_5->pPortName ? printer_info_5->pPortName : L"";
    printerInfo5.PrinterName = printer_info_5->pPrinterName ? printer_info_5->pPrinterName : L"";
    printerInfo5.TransmissionRetryTimeout = printer_info_5->TransmissionRetryTimeout;

    return printerInfo5;
}

std::wstring PrinterInfo5ToString(const  PrinterInfo5& printerInfo5)
{
    std::wostringstream ostr;
    ostr << "PRINTER_INFO_5" << std::endl;
    ostr << "  Attributes:      " << printerInfo5.Attributes << std::endl;
    auto attribbutesString = PrinterAttributesToString(printerInfo5.Attributes);
    ostr << "  " << attribbutesString << std::endl;
    ostr << "  DeviceNotSelectedTimeout:    " << printerInfo5.DeviceNotSelectedTimeout << std::endl;
    ostr << "  PortName:                    " << printerInfo5.PortName << std::endl;
    ostr << "  PrinterName:                 " << printerInfo5.PrinterName << std::endl;
    ostr << "  TransmissionRetryTimeout:    " << printerInfo5.TransmissionRetryTimeout << std::endl;
    const std::wstring result(ostr.str());
    return result;
}

int wmain(int argc, wchar_t *argv[])
{
    std::wstring printerName = L"xps card printer";
    if (argc > 1) {
        printerName = argv[1];
    }

    HANDLE printerHandle {};
    int rc = ::OpenPrinterW((LPWSTR) printerName.c_str(), &printerHandle, nullptr);
    if (0 == rc) {
        const auto lastError = ::GetLastError();
        std::wcerr << "OpenPrinterW() fail: " << lastError << " " << GetWin32ErrString(lastError) << std::endl;
        std::exit(-1);
    }

    std::wcout << printerName << std::endl;

    const auto printerInfo1 = GetPrinterInfo1(printerHandle);
    const auto printerInfo1String = PrinterInfo1ToString(printerInfo1);
    std::wcout << printerInfo1String << std::endl;

    const auto printerInfo2 = GetPrinterInfo2(printerHandle);
    const auto printerInfo2String = PrinterInfo2ToString(printerInfo2);
    std::wcout << printerInfo2String << std::endl;

    const auto printerInfo5 = GetPrinterInfo5(printerHandle);
    const auto printerInfo5String = PrinterInfo5ToString(printerInfo5);
    std::wcout << printerInfo5String << std::endl;

    // dlftodo: PRINTER_INFO_8;
    //          PRINTER_INFO9;

    rc = ::ClosePrinter(printerHandle);
    if (0 == rc) {
        const auto lastError = ::GetLastError();
        std::wcerr << "ClosePrinter() fail: " << lastError << " " << GetWin32ErrString(lastError) << std::endl;
        std::exit(-1);
    }
}