#include "stdafx.h"
#include <string>
#include <atlstr.h>
#include "myclass.h"

STDMETHODIMP Cmyclass::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* const arr[] = {
        &IID_Imyclass
    };
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        if (InlineIsEqualGUID(*arr[i], riid))
            return S_OK;
    }
    return S_FALSE;
}

STDMETHODIMP Cmyclass::stringFromInt2(int anInt, BSTR* aString)
{
    const CStringW result = std::to_wstring(anInt).c_str();
    *aString = result.AllocSysString();
    return S_OK;
}