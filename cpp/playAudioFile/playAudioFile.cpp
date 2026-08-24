#include <iostream>
#include <Windows.h>

void usage(WCHAR* arg)
{
    std::wcout << L"play an mp3 file and exit." << std::endl;
    std::wcout << L"usage: " << arg << L" <file>" << std::endl;
}

// Send a string to the Media Control Interface
// If an error occurs, display it and the string
// that produced the error.
void sendMCICommand(std::wstring s)
{
    MCIERROR rc = ::mciSendString(s.c_str(), NULL, 0, 0);
    if (rc)
    {
        std::wcout << L"err " << rc << L" calling mcdSendStringW()." << std::endl;
    }
}

int wmain(int argc, WCHAR* args[])
{
    const int BUFSIZE{ 4096 };

    if (argc < 2)
    {
        usage(args[0]);
        return 0;
    }

    WCHAR buffer[BUFSIZE]{ 0 };
    WCHAR buf[BUFSIZE]{ 0 };
    DWORD retval = ::GetShortPathNameW(
        args[1],
        buf,
        BUFSIZE);
    if (retval == 0)
    {
        std::wcout << L"GetShortPathNameW() failed (" << ::GetLastError() << L")" << std::endl;
        return 0;
    }

    sendMCICommand(L"close all");

    std::wstring command = L"open ";
    command += buf;
    command += L" Type MPEGVideo Alias theMP3";
    sendMCICommand(command);

    sendMCICommand(L"Play theMP3 Wait");
}