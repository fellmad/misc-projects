#include "stdafx.h"
#include <WinSpool.h>
#include <atlstr.h>
#include <atlcoll.h>
#include <iostream>

void usage(TCHAR* argv[])
{
    std::cout << "usage: " << CT2A(argv[0]) << " <printername>" << std::endl;
    ::exit(-1);
}

void print_form_info_2(FORM_INFO_2 formInfo2)
{
    std::wcout << L"name: " << formInfo2.pName << std::endl;
    std::wcout << L"  flags: " << std::hex << formInfo2.Flags << std::dec;
    std::wstring flags = formInfo2.Flags & FORM_USER ? L"FORM_USER " : L"";
    flags += formInfo2.Flags & FORM_BUILTIN ? L"FORM_BUILTIN " : L"";
    flags += formInfo2.Flags & FORM_PRINTER ? L"FORM_PRINTER " : L"";

    std::wcout << L"  size: " << formInfo2.Size.cx << L"," << formInfo2.Size.cy << std::endl;
    std::wcout << L"  top,left,right,bottom: "
        << formInfo2.ImageableArea.top
        << L"," << formInfo2.ImageableArea.left
        << L"," << formInfo2.ImageableArea.right
        << L"," << formInfo2.ImageableArea.bottom
        << std::endl;
    std::cout << "  keyword: " << (formInfo2.pKeyword ? formInfo2.pKeyword : "(nullptr)") << std::endl;

    std::wcout << L"  stringtype: " << std::hex << formInfo2.StringType << std::dec << L": ";
    std::wstring stringType = formInfo2.StringType & STRING_NONE ? L"STRING_NONE " : L"";
    stringType += formInfo2.StringType & STRING_MUIDLL ? L"STRING_MUIDLL " : L"";
    stringType += formInfo2.StringType & STRING_LANGPAIR ? L"STRING_LANGPAIR " : L"";
    std::wcout << stringType.c_str() << std::endl;
    std::wcout << L"  muiDll: " << (formInfo2.pMuiDll ? formInfo2.pMuiDll : L"(nullptr)") << std::endl;
    std::wcout << L"  resourceId: " << formInfo2.dwResourceId << std::endl;
    std::wcout << L"  displayName: " << (formInfo2.pDisplayName ? formInfo2.pDisplayName : L"(nullptr)") << std::endl;
    std::wcout << L"  langId: " << formInfo2.wLangId << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc < 2) {
        usage(argv);
    }
    const CString printerName = argv[1];

    HANDLE printerHandle(0);
    int rc = ::OpenPrinter(CT2W(printerName), &printerHandle, nullptr);
    if (0 == rc) {
        std::wcout << L"OpenPrinter(): " << ::GetLastError() << std::endl;
        ::exit(-1);
    }

    DWORD needed(0);
    DWORD returned(0);
    rc = ::EnumForms(printerHandle, 2, nullptr, 0, &needed, &returned);
    DWORD dw = ::GetLastError();
    if (ERROR_INSUFFICIENT_BUFFER != dw) {
        std::wcout << L"EnumForms() to get buffer size: " << dw << std::endl;
        ::exit(-1);
    }

    FORM_INFO_2* form_info_2s = (FORM_INFO_2*) new BYTE[needed];
    rc = ::EnumForms(printerHandle, 2, (PBYTE) form_info_2s, needed, &needed, &returned);
    if (0 == rc) {
        std::wcout << L"EnumForms(): " << ::GetLastError() << std::endl;
        ::exit(-1);
    }

    for (DWORD i = 0; i < returned; i++) {
        print_form_info_2(form_info_2s[i]);
    }

    return 0;
}