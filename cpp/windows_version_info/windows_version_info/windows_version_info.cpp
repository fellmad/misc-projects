#include <SDKDDKVer.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <VersionHelpers.h>

int main()
{
    OSVERSIONINFOW osversioninfow = {};
    osversioninfow.dwOSVersionInfoSize = sizeof osversioninfow;
    const auto returnCode = ::GetVersionExW(&osversioninfow);
    std::wcout << "dwMajorVersion: " << osversioninfow.dwMajorVersion << std::endl;
    std::wcout << "dwMinorVersion: " << osversioninfow.dwMinorVersion << std::endl;
    std::wcout << "dwBuildNumber:  " << osversioninfow.dwBuildNumber << std::endl;
    std::wcout << "dwPlatformId:   " << osversioninfow.dwPlatformId << std::endl;
}