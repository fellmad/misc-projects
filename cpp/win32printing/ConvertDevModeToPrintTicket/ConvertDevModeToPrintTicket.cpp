////////////////////////////////////////////////////////////////////////////////
//
// win32 functions that use the print ticket 'scope':
//  PTMergeAndValidatePrintTicket()
//  PTConvertPrintTicketToDevMode()
//  PTConvertDevModeToPrintTicket()     // only function used in this app
//
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>
#include <prntvpt.h>
#include <string>
#include <vector>
#include <WinSpool.h>
#include "XGetopt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void usage(TCHAR* appname)
{
    std::cout << std::endl;
    std::cout << "usage: " << CT2A(appname) << " [-s <scope>]" << std::endl;
    std::cout << " " << "-s page: use page-level printticket for PTConvertDevModeToPrintTicket()" << std::endl;
    std::cout << " " << "-s doc:  doc-level" << std::endl;
    std::cout << " " << "-s job:  job-level" << std::endl;
    std::cout << " " << "default: job-level" << std::endl;
    exit(0);
}

std::wstring MergeScopeToString(const EPrintTicketScope scope)
{
    std::wstring scopeString {TEXT("bad scope")};
    switch (scope) {
    case kPTDocumentScope: scopeString = TEXT("kPTDocumentScope"); break;
    case kPTJobScope: scopeString = TEXT("kPTJobScope"); break;
    case kPTPageScope: scopeString = TEXT("kPTPageScope"); break;
    }
    return scopeString;
}

int _tmain(int argc, TCHAR* argv[])
{
    if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)) {
        std::wcerr << "Fatal Error: MFC initialization failed" << std::endl;
        return -1;
    }

    EPrintTicketScope printTicketScope {kPTJobScope};

    int c(0);
    while ((c = getopt(argc, argv, TEXT("s:h?"))) != EOF) {
        switch (c) {
        case TEXT('h'):
        case TEXT('?'):
            usage(argv[0]);
            break;

        case TEXT('s'):
        {
            if (optarg) {
                if (CString(optarg) == TEXT("page")) {
                    printTicketScope = kPTPageScope; break;
                }
                if (CString(optarg) == TEXT("doc")) {
                    printTicketScope = kPTDocumentScope; break;
                }
                if (CString(optarg) == TEXT("job")) {
                    printTicketScope = kPTJobScope; break;
                }
            }
            usage(argv[0]);
        }
        break;
        }
    }

    CString s;
    CPrintDialog pd(false);
    if (pd.DoModal() != IDOK) {
        std::wcerr << "no printer selected." << std::endl;
        return -2;
    }

    DWORD maxSchemaVersion {};
    int rc = ::PTQuerySchemaVersionSupport(pd.GetDeviceName().GetBuffer(), &maxSchemaVersion);
    if (FAILED(rc)) {
        std::wcerr << "PTQuerySchemaVersionSupport(): " << ::GetLastError() << std::endl;
        return rc;
    }

    HPTPROVIDER provider {};
    rc = ::PTOpenProvider(pd.GetDeviceName().GetBuffer(), maxSchemaVersion, &provider);
    if (FAILED(rc)) {
        std::wcerr << "DPTOpenProvider(): " << ::GetLastError() << std::endl;
        return rc;
    }

    HGLOBAL hglobal {};
    CComPtr <IStream> stream;
    rc = ::CreateStreamOnHGlobal(hglobal, false, &stream);
    if (FAILED(rc)) {
        std::wcerr << "CreateStreamOnHGlobal(): " << ::GetLastError() << std::endl;
        return rc;
    }

    rc = ::DocumentProperties(
        NULL,
        pd.m_pd.hInstance,
        pd.GetDeviceName().GetBuffer(),
        NULL,
        NULL,
        0);
    if (rc < 0) {
        std::wcerr << "DocumentProperties(): " << ::GetLastError() << std::endl;
        return rc;
    }

    const int devModeSize = rc;
    std::wcerr << "devmode size in bytes: " << devModeSize << std::endl;

    std::wcerr << "using " << MergeScopeToString(printTicketScope) << " for PTConvertDevModeToPrintTicket()" << std::endl;

    rc = ::PTConvertDevModeToPrintTicket(
        provider,
        devModeSize,
        pd.GetDevMode(),
        printTicketScope,
        stream);
    if (FAILED(rc)) {
        std::wcerr << "PTConvertDevModeToPrintTicket(): " << ::GetLastError() << std::endl;
        return rc;
    }

    rc = stream->Commit(0);
    if (FAILED(rc)) {
        std::wcerr << "stream->Commit(): " << ::GetLastError() << std::endl;
        return rc;
    }

    // get the output stream / printticket size:
    LARGE_INTEGER pos1 = {0};
    ULARGE_INTEGER pos2 = {0};
    rc = stream->Seek(pos1, STREAM_SEEK_END, &pos2);
    if (FAILED(rc)) {
        std::wcerr << "stream->Seek(): " << ::GetLastError() << std::endl;
        return rc;
    }

    const int streamSize = pos2.LowPart;

    // rewind printticket stream for read:
    rc = stream->Seek(pos1, STREAM_SEEK_SET, &pos2);
    if (FAILED(rc)) {
        std::wcerr << "stream->Seek(): " << ::GetLastError() << std::endl;
        return rc;
    }

    std::vector <byte> pngByteBuffer(streamSize, 0);

    ULONG bytesRead(0);
    rc = stream->Read(&pngByteBuffer[0], streamSize, &bytesRead);
    if (FAILED(rc)) {
        std::wcerr << "stream->Read(): " << ::GetLastError() << std::endl;
        return rc;
    }

    for (int i = 0; i < streamSize; i++) {
        std::cout << pngByteBuffer[i];
    }

    rc = ::PTCloseProvider(provider);
    if (FAILED(rc)) {
        std::wcerr << "PTCloseProvider(): " << ::GetLastError() << std::endl;
        return rc;
    }

    return rc;
}