#include <iostream>
#include <regex>

int main()
{
    // original:
    // std::regex      reg("([\\w]+)");
    std::wregex /**/ reg(LR"(([\w]+))");
    while (true) {
        std::cout << "Enter a string to split (q=quit): ";
        std::wstring str;
        if (!getline(std::wcin, str) || str == L"q")
            break;

        const std::wsregex_iterator end;
        for (std::wsregex_iterator it(str.begin(), str.end(), reg); it != end; ++it) {
            std::wcout << "\"" << (*it)[0] << "\"" << std::endl;
        }
    }
}