#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <list>
#include <atlstr.h>

int main()
{
    std::list <CStringW> moduleFileNames 
    {
        L"dxp01enu_32bit.dll",
        L"dxp01enu_64bit.dll",
        L"dxp01enu_32bit.res",
        L"dxp01enu_32bit.res"
    };

    for (CStringW moduleFileName : moduleFileNames) {
        auto module = ::LoadLibraryExW(
            moduleFileName,
            nullptr,
            LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE);
        if (nullptr == module) {
            auto lasterror = ::GetLastError();
            std::wcout << L"::LoadLibraryExW(" << moduleFileName.GetBuffer() << L") fail: " << lasterror << std::endl;
        }
        else {
            std::wcout << L"::LoadLibraryExW(" << moduleFileName.GetBuffer() << L") success." << std::endl;
            ::FreeLibrary(module);
        }
    }
}
