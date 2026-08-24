// https://learn.microsoft.com/en-us/cpp/cpp/main-function-command-line-args?view=msvc-170
// https://learn.microsoft.com/en-us/cpp/c-language/using-wmain?view=msvc-170

#include <iostream>
#include <vector>

static void usage()
{
    std::wcout << "splitenv <environment variable> [delimiter]" << std::endl;
    ::exit(-1);
}

std::vector <std::wstring> split(std::wstring envPath, const std::wstring delim) {
    std::vector<std::wstring> tokens;
    size_t pos = 0;
    std::wstring token;
    while ((pos = envPath.find(delim)) != std::wstring::npos) {
        token = envPath.substr(0, pos);
        tokens.push_back(token);
        envPath.erase(0, pos + delim.length());
    }
    tokens.push_back(envPath);
    return tokens;
}

int wmain(int argc, wchar_t* argv[])
{
    std::wstring appName = argv[0];
    if (argc < 2) usage();

    std::wstring env_var = argv[1];
    std::wstring delim = L";";
    if (argc > 2) delim = argv[2];

    size_t required_size{};
    ::_wgetenv_s(
        &required_size,
        nullptr,
        0,
        env_var.c_str());
    if (!required_size) {
        std::wcerr << env_var << " not found" << std::endl;
        ::exit(-1);
    }

    std::shared_ptr <wchar_t> buf{
        new wchar_t [required_size] {}
    };
    ::_wgetenv_s(
        &required_size,
        buf.get(),
        required_size,
        env_var.c_str());

    std::wstring buffer(buf.get());
    auto split_items = split(buffer, delim);
    for (auto split_item : split_items) {
        std::wcout << split_item << std::endl;
    }
}