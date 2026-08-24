#include "stdafx.h"
#include "../win32dll/win32dll.h"

int wmain()
{
    auto result = IsWindows10();
    wprintf(L"IsWindows10() returned %d the first time\n", result);

    result = IsWindows10();
    wprintf(L"IsWindows10() returned %d the 2nd time\n", result);

    result = IsWindows10();
    wprintf(L"IsWindows10() returned %d the 3rd time\n", result);
}