#include <SDKDDKVer.h>
#include <filesystem>
#include <iostream>
#include <atlstr.h>

namespace fs = std::tr2::sys;

int _tmain(int argc, _TCHAR* argv[])
{
    const std::wstring short_ini_filename(L"an_ini.ini");

    WCHAR* currentPathBuf = _wgetcwd(nullptr, 0);
    fs::wpath long_ini_filename {currentPathBuf};
    free(currentPathBuf);
    long_ini_filename /= short_ini_filename;
    ATLASSERT(fs::exists(long_ini_filename));

    std::wcout << "reading from: " << long_ini_filename << std::endl;
    const auto sectionName = L"a section name";
    auto keyName = L"key_name_1";

    CStringW valueRead;
    const int max = 255;
    DWORD returnedCharCount = ::GetPrivateProfileStringW(
        sectionName,
        keyName,
        L"",
        valueRead.GetBuffer(max),
        max,
        long_ini_filename.file_string().c_str());
    ATLASSERT(returnedCharCount > 0);
    valueRead.ReleaseBuffer();
    std::wcout << "read: " << keyName << ", " << valueRead.GetBuffer() << std::endl;

    keyName = L"key_name_2";
    valueRead.Empty();
    returnedCharCount = ::GetPrivateProfileStringW(
        sectionName,
        keyName,
        L"",
        valueRead.GetBuffer(max),
        max,
        long_ini_filename.file_string().c_str());
    ATLASSERT(returnedCharCount > 0);
    valueRead.ReleaseBuffer();
    std::wcout << "read: " << keyName << ", " << valueRead.GetBuffer() << std::endl;

    keyName = L"key_name_3";
    valueRead.Empty();
    returnedCharCount = ::GetPrivateProfileStringW(
        sectionName,
        keyName,
        L"",
        valueRead.GetBuffer(max),
        max,
        long_ini_filename.file_string().c_str());
    ATLASSERT(returnedCharCount > 0);
    valueRead.ReleaseBuffer();
    std::wcout << "read: " << keyName << ", " << valueRead.GetBuffer() << std::endl;

    keyName = L"key_name_4";
    valueRead.Empty();
    returnedCharCount = ::GetPrivateProfileStringW(
        sectionName,
        keyName,
        L"",
        valueRead.GetBuffer(max),
        max,
        long_ini_filename.file_string().c_str());
    ATLASSERT(0 == returnedCharCount);
    valueRead.ReleaseBuffer();
    std::wcout << "read: " << keyName << ", " << valueRead.GetBuffer() << std::endl;

    keyName = L"int_key_name_1";
    UINT uint_val = ::GetPrivateProfileIntW(
        sectionName,
        keyName,
        0,
        long_ini_filename.file_string().c_str());
    ATLASSERT(0 != uint_val);
    std::wcout << "read: " << keyName << ", " << uint_val << std::endl;

    keyName = L"int_key_name_2";
    uint_val = ::GetPrivateProfileIntW(
        sectionName,
        keyName,
        0,
        long_ini_filename.file_string().c_str());
    ATLASSERT(0 != uint_val);
    ATLASSERT(0x123 == uint_val);   // YAY! we can read hex vals from an INI file.
    std::wcout << "read: " << keyName << ", " << uint_val << std::endl;

    keyName = L"int_key_name_3";
    uint_val = ::GetPrivateProfileIntW(
        sectionName,
        keyName,
        0,
        long_ini_filename.file_string().c_str());
    ATLASSERT(-3 == uint_val);
    std::wcout << "read: " << keyName << ", " << uint_val << std::endl;

    return 0;
}
