#include <iostream>
#include <regex>

int main()
{
    std::wregex r(LR"(//\s*(.+))");
    while (true) {
        std::cout << "Enter a string with optional code comments (q=quit): ";
        std::wstring str;
        if (!getline(std::wcin, str) || str == L"q")
            break;
        std::wsmatch m;
        if (std::regex_search(str, m, r))
            std::wcout << "  Found comment '" << m[1] << "'" << std::endl;
        else
            std::wcout << L"  No comment found!" << std::endl;
    }
}
