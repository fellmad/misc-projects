#include <iostream>
#include <regex>
#include <vector>

int main()
{
    std::regex reg("^(\\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])$");
    while (true) {
        std::cout << "Enter a date (year/month/day) (q=quit): ";
        std::string str;
        if (!getline(std::cin, str) || str == "q")
            break;

        std::vector <int> vec = {2, 3};
        const std::sregex_token_iterator end;
        for (std::sregex_token_iterator iter(str.begin(), str.end(), reg, vec);
                iter != end; ++iter) {
            std::cout << "\"" << *iter << "\"" << std::endl;
        }
    }
}