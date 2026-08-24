#include "stdafx.h"
#include "win32dll.h"

// This is an example of an exported variable
WIN32DLL_API int nwin32dll = 0;

// This is an example of an exported function.
WIN32DLL_API int IsWindows10(void)
{
    static BOOL bWindows10 = FALSE;
    static BOOL bGotVersion = FALSE;

    /* return cached value if we already checked Windows version */
    if (!bGotVersion) {
        OSVERSIONINFO VersionInformation;
        VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (GetVersionEx(&VersionInformation) != 0) {
            if (
                VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT &&
                VersionInformation.dwMajorVersion >= 10) {
                bWindows10 = TRUE;
                wprintf(L"got windows 10\n");
            }
            else {
                wprintf(L"got something other than windows 10\n");
                wprintf(L"VersionInformation.dwPlatformId: %d\n", VersionInformation.dwPlatformId);
                wprintf(L"VersionInformation.dwMajorVersion: %d\n", VersionInformation.dwMajorVersion);
            }

            bGotVersion = TRUE;
        }
        else {
            wprintf(L"GetVersionEx() err: %d\n", ::GetLastError());
        }
    }
    else {
        wprintf(L"already got version info\n");
    }

    return bWindows10;
}

// This is the constructor of a class that has been exported.
// see win32dll.h for the class definition
Cwin32dll::Cwin32dll()
{
    return;
}