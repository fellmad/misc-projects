#include "stdafx.h"
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <../../com_server/com_server_i.h>
#include "safecoinit.h"

inline std::wstring trim(const std::wstring &s)
{
    auto wsfront = std::find_if_not(s.begin(), s.end(), [] (int c) {return std::isspace(c); });
    auto wsback = std::find_if_not(s.rbegin(), s.rend(), [] (int c) {return std::isspace(c); }).base();
    const auto result = (wsback <= wsfront ? std::wstring() : std::wstring(wsfront, wsback));
    return result;
}

std::wstring GetWin32ErrString(const DWORD rc)
{
    const UINT maxMessageLength {1024};
    WCHAR message[maxMessageLength] {};
    const DWORD formatMessageResult = ::FormatMessageW(
        FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr,
        rc,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        message,
        1024,
        nullptr);
    std::wstring result = message;

    if (!formatMessageResult) {
        std::wcerr << "FormatMessageW() fail: " << formatMessageResult << std::endl;
    }

    result = trim(result);
    return result;
}

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

MIDL_DEFINE_GUID(CLSID, CLSID_myclass, 0x02704B97, 0x30C1, 0x41A9, 0x82, 0xD2, 0x47, 0x64, 0x69, 0xDD, 0x30, 0xFB);

int main()
{
    const std::wstring comDllName(L"com_server.dll");

    const HMODULE comDllHandle = ::LoadLibraryW(comDllName.c_str());
    if (nullptr == comDllHandle) {
        std::wcerr << "LoadLibraryW() fail: " << ::GetLastError() << " " << GetWin32ErrString(::GetLastError()) << std::endl;
        std::exit(-1);
    }

    typedef HRESULT(__stdcall *pfnDllGetClassObject) (REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);

    const auto pDllGetClassObj = reinterpret_cast<pfnDllGetClassObject> (::GetProcAddress(comDllHandle, "DllGetClassObject"));
    if (nullptr == pDllGetClassObj) {
        std::wcerr << "GetProcAddress(DllGetClassObject) fail: " << ::GetLastError() << " " << GetWin32ErrString(::GetLastError()) << std::endl;
        std::exit(-1);
    }

    SafeCoInit safeCoinit;

    CComPtr <Imyclass> myInterface;

    HRESULT hr = myInterface.CoCreateInstance(CLSID_myclass);
    if (FAILED(hr)) {
        std::wcerr << "myInterface.CoCreateInstance() fail: " << ::GetLastError() << " " << GetWin32ErrString(::GetLastError()) << std::endl;
        std::exit(-1);
    }

    hr = ::FreeLibrary(comDllHandle);
    if (FAILED(hr)) {
        std::wcerr << "FreeLibrary() fail: " << ::GetLastError() << " " << GetWin32ErrString(::GetLastError()) << std::endl;
        std::exit(-1);
    }
}