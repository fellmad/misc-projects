#include "stdafx.h"
#include <WinSpool.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
    const CComBSTR printerName = L"xps card printer";
    const CComBSTR formName = L"ISO ID-1 (85.60 x 53.98 mm)";

    std::wcout << "deleting form " << formName.m_str << " for printer " << printerName.m_str << std::endl;
    HANDLE printerHandle(nullptr);
    int rc = ::OpenPrinter(printerName, &printerHandle, NULL);
    if (0 == rc) {
        std::wcout << L"OpenPrinter(): " << ::GetLastError() << std::endl;
        ::exit(-1);
    }

    rc = ::DeleteForm(printerHandle, formName);
    if (0 == rc) {
        std::wcout << L"DeleteForm(): " << ::GetLastError() << std::endl;
        ::exit(-1);
    }

    return 0;
}