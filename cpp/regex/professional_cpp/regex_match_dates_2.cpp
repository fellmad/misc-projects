#include <iostream>
#include <regex>

int main()
{
    std::wregex r(L"^(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])$");
    while (true)  {
        std::wcout << "Enter a date (year/month/day) (q=quit): ";
        std::wstring str;
        if (!getline(std::wcin, str) || str == L"q") {
            std::exit(0);
        }

        std::wsmatch m;
        if (regex_match(str, m, r)) {
            std::wcout << "match: " << m[0] << std::endl;
            int year        = std::stoi(m[1].str());
            int month       = std::stoi(m[2]); // don't need str()
            const auto day  = std::stoi(m[3]);
            std::cout << "  Valid date: year: " << year << "; month: " << month << "; day: " << day << std::endl;
        } else {
            std::cout << "  Invalid date!" << std::endl;
        }
    }
}