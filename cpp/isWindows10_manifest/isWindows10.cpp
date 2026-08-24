#include <windows.h>
#include "stdafx.h"

/* returns TRUE if OS is Windows 10 and above... */
BOOL IsWindows10OrGreater()
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

int wmain()
{
    auto isWindows10 = IsWindows10OrGreater();
    wprintf(L"IsWindows10OrGreater() returned first %d\n", isWindows10);

    isWindows10 = IsWindows10OrGreater();
    wprintf(L"IsWindows10OrGreater() returned 2nd %d\n", isWindows10);

    isWindows10 = IsWindows10OrGreater();
    wprintf(L"IsWindows10OrGreater() returned 3rd %d\n", isWindows10);

    wprintf(L"press any key\n");
    getchar();

}
