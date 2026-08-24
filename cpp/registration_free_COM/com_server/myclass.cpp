// myclass.cpp : Implementation of Cmyclass

#include "stdafx.h"
#include "myclass.h"

// Cmyclass

STDMETHODIMP Cmyclass::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* const arr[] =
    {
        &IID_Imyclass
    };

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        if (InlineIsEqualGUID(*arr[i], riid))
            return S_OK;
    }
    return S_FALSE;
}