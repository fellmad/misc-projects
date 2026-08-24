// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamea

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

const int BUFSIZE{ 4096 };

int wmain(int argc, WCHAR* argv[])
{
    DWORD  retval = 0;
    WCHAR buffer[BUFSIZE]{ 0 };
    WCHAR buf[BUFSIZE]{ 0 };
    WCHAR** lppPart{ 0 };

    if (argc != 2)
    {
        std::wcout << L"usage: " << argv[0] << L" [file]" << std::endl;
        return 0;
    }

    // Retrieve the full path name for a file. The file does not need to exist.
    retval = ::GetFullPathNameW(
        argv[1],
        BUFSIZE,
        buffer,
        lppPart);
    if (retval == 0)
    {
        std::wcout << L"GetFullPathNameW() failed (" << ::GetLastError() << L")" << std::endl;
        return 0;
    }
    std::wcout << L"GetFullPathNameW():" << std::endl << buffer << std::endl;

    if (lppPart != nullptr && *lppPart != nullptr)
    {
        std::wcout << L"The final component in the path name is: " << *lppPart << std::endl;
    }

    // Retrieve the short path name.
    retval = ::GetShortPathNameW(
        argv[1],
        buf,
        BUFSIZE);
    if (retval == 0)
    {
        std::wcout << L"GetShortPathNameW() failed (" << ::GetLastError() << L")" << std::endl;
        return 0;
    }

    std::wcout << L"GetShortPathNameW():" << std::endl << buf << std::endl;

    // Retrieve the long path name.
    retval = ::GetLongPathNameW(
        buf,
        buffer,
        BUFSIZE);
    if (retval == 0)
    {
        std::wcout << L"GetLongPathNameW() failed (" << ::GetLastError() << L")" << std::endl;
        return 0;
    }

    std::wcout << L"GetLongPathNameW():" << std::endl << buffer << std::endl;
}