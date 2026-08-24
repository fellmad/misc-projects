#include <SDKDDKVer.h>
#include <afxdlgs.h>
#include <atlstr.h>
#include <prntvpt.h>
#include <WinSpool.h>
#include <iostream>
#include <vector>

int wmain(int /*argc*/, _TCHAR* /*argv*/[])
{
    CPrintDialog pd(false);
    if (pd.DoModal() != IDOK) {
        ::exit(-1);
    }

    const CStringW deviceName = pd.GetDeviceName();

    DWORD maxSchemaVersion(0);
    int rc = ::PTQuerySchemaVersionSupport(deviceName, &maxSchemaVersion);
    if (FAILED(rc)) {
        std::wcerr << "PTQuerySchemaVersionSupport(" << (LPCWSTR) deviceName << "): " << rc << std::endl;
        ::exit(-1);
    }

    HPTPROVIDER provider(0);
    rc = ::PTOpenProvider(deviceName, maxSchemaVersion, &provider);
    if (FAILED(rc)) {
        std::wcerr << "PTOpenProvider(" << (LPCWSTR) deviceName << "): " << rc << std::endl;
        ::exit(-1);
    }

    HGLOBAL hglobalPrintCapabilities {};
    CComPtr <IStream> printCapabilitiesStream;

    rc = ::CreateStreamOnHGlobal(hglobalPrintCapabilities, true, &printCapabilitiesStream);
    if (FAILED(rc)) {
        std::wcerr << "CreateStreamOnHGlobal(): " << rc << std::endl;
        ::exit(-1);
    }

    CComBSTR errmsg;
    rc = ::PTGetPrintCapabilities(
        provider,
        nullptr,
        printCapabilitiesStream,
        &errmsg);
    if (FAILED(rc)) {
        std::wcerr << "PTGetPrintCapabilities(): " << rc << "; ";
        if (errmsg.Length()) {
            std::wcerr << (LPWSTR) errmsg << std::endl;
        }
        else {
            std::wcerr << "no errormessage returned." << std::endl;
        }
        ::exit(-1);
    }

    rc = ::PTCloseProvider(provider);
    if (FAILED(rc)) {
        std::wcerr << "PTCloseProvider(): " << rc << std::endl;
        ::exit(-1);
    }

    LARGE_INTEGER pos1 {};
    ULARGE_INTEGER pos2 {};
    rc = printCapabilitiesStream->Seek(pos1, STREAM_SEEK_END, &pos2);
    if (FAILED(rc)) {
        std::wcerr << "printCapabilitiesStream->Seek()" << rc << std::endl;
        ::exit(-1);
    }
    const auto streamSize = pos2.LowPart;

    // rewind printcapabilities stream for read:
    pos1 = {};
    pos2 = {};
    rc = printCapabilitiesStream->Seek(pos1, STREAM_SEEK_SET, &pos2);
    if (FAILED(rc)) {
        std::wcerr << "printCapabilitiesStream->Seek()" << rc << std::endl;
        ::exit(-1);
    }

    std::vector <byte> printCapabilitiesBuf(streamSize);
    ULONG bytesRead {};
    rc = printCapabilitiesStream->Read(&printCapabilitiesBuf[0], streamSize, &bytesRead);
    if (FAILED(rc)) {
        std::wcerr << "printCapabilitiesStream->Read()" << rc << std::endl;
        ::exit(-1);
    }

    for (const auto& eachByte : printCapabilitiesBuf) {
        std::cout << eachByte;
    }
}