#include <windows.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <atlstr.h>
#include <codecvt>

namespace fs = std::filesystem;

// for std:string, std::wstring conversions:
// https://codereview.stackexchange.com/questions/419/converting-between-stdwstring-and-stdstring
// todo: see https://en.cppreference.com/w/cpp/locale/wstring_convert
//      ...or https://en.cppreference.com/w/cpp/locale/codecvt

std::wstring utf8ToUtf16(const std::string &utf8Str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.from_bytes(utf8Str);
}

std::string utf16ToUtf8(const std::wstring &utf16Str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.to_bytes(utf16Str);
}

int wmain(int argc, WCHAR *argv[])
{
    if (argc != 2)
    {
        fs::path filename_path(argv[0]);
        std::wcout << L"usage: " << filename_path.filename() << L" [target_file]" << std::endl;
        return 0;
    }

    const auto &short_filename = argv[1];
    const int buf_len{_MAX_PATH};
    WCHAR long_filename[buf_len]{};
    const auto searchPathResult = ::SearchPathW(
        nullptr,
        short_filename,
        nullptr,
        buf_len,
        long_filename,
        nullptr);
    if (!searchPathResult)
    {
        std::wcout << L"did not find " << short_filename << std::endl;
        std::exit(1);
    }

    std::wcout << L"file: " << long_filename << std::endl;

    fs::path filename_path(long_filename);

    std::wstring just_the_path = filename_path.parent_path();
    std::wcout << L"path: " << just_the_path << std::endl;

    std::wstring pushd_command = L"cmd.exe pushd " + just_the_path;

    pushd_command = L"pushd c:\\";
    std::wcout << L"command: " << pushd_command << std::endl;
    std::string astring = utf16ToUtf8(pushd_command);
    std::system(astring.c_str());
}