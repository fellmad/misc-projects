#include <windows.h>
#include <string>
#include <iostream>

int wmain(int argc, WCHAR* argv[])
{
    if (argc != 2) {
        std::wcout << L"usage: " << argv[0] << L" [target_file]" << std::endl;
        return 0;
    }

    const auto& short_filename = argv[1];
    const int buf_len{ _MAX_PATH };
    WCHAR long_filename[buf_len]{};

    const auto searchPathResult = ::SearchPathW(
        nullptr,
        short_filename,
        nullptr,
        buf_len,
        long_filename,
        nullptr);
    if (searchPathResult) {
        std::wcout << long_filename << std::endl;
    }
    else {
        std::wcout << L"did not find " << short_filename << std::endl;
    }
}