#include <iostream>
#include <regex>

int main()
{
    // original:
    // std::wregex   r(L"^\\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1])$");
    std::wregex r(LR"xxx(^\d{4}/(?:0?[1-9]|1[0-2])/(?:0?[1-9]|[1-2][0-9]|3[0-1])$)xxx");
    while (true) {
        std::wcout << "Enter a date (year/month/day) (q=quit): ";
        std::wstring str;
        if (!getline(std::wcin, str) || str == L"q")
            break;
        if (std::regex_match(str, r))
            std::wcout << "  Valid date." << std::endl;
        else
            std::wcout << "  Invalid date!" << std::endl;
    }
}