// use taskmgr to see mem size...

// june 3, 2015: looks like p.Release() and 'p = nulptr' are same...

#include "stdafx.h"
#include <iostream>

HRESULT CheckComError_SmartPtr()
{
    CComPtr<IErrorInfo> pErrInfo;
    HRESULT hr = ::GetErrorInfo(0, &pErrInfo);
    if (FAILED(hr)) {
        std::cerr << "GetErrorInfo() " << hr << std::endl;
        throw hr;
    }

    CComBSTR bstrDescription;
    hr = pErrInfo->GetDescription(&bstrDescription);
    if (FAILED(hr)) {
        std::cerr << "pErrInfo->GetDescription() " << hr << std::endl;
        throw hr;
    }

    CComBSTR bstrSource;
    hr = pErrInfo->GetSource(&bstrSource);
    if (FAILED(hr)) {
        std::cerr << "pErrInfo->GetSource() " << hr << std::endl;
        throw hr;
    }

    CComBSTR bstrHelpFile;
    hr = pErrInfo->GetHelpFile(&bstrHelpFile);
    if (FAILED(hr)) {
        std::cerr << "pErrInfo->GetHelpFile() " << hr << std::endl;
        throw hr;
    }

    pErrInfo.Release();
    // pErrInfo = nullptr;

    return S_OK;
}

int main()
{
    for (auto i = 0; i < 1000000; i++) {
        CheckComError_SmartPtr();
    }

    std::cout << std::endl << "press any key";
    getchar();
}
