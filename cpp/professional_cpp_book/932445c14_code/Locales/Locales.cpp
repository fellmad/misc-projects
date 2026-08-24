#include <iostream>
#include <string>
#include <locale>

int main()
{
    std::locale loc("");

    std::cout << loc.name() << std::endl;

    if (
        loc.name().find("en_US") == std::string::npos &&
        loc.name().find("United States") == std::string::npos) {
        std::wcout << L"Welcome non-U.S. English speaker!" << std::endl;
    }
    else {
        std::wcout << L"Welcome U.S. English speaker!" << std::endl;
    }
}