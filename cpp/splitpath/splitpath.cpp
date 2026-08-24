#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

std::vector <std::string> split(std::string envPath, const std::string delim) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = envPath.find(delim)) != std::string::npos) {
        token = envPath.substr(0, pos);
        tokens.push_back(token);
        envPath.erase(0, pos + delim.length());
    }
    tokens.push_back(envPath);
    return tokens;
}

int main() {
    size_t required_size{};
    getenv_s(&required_size, nullptr, 0, "path");
    if (0 == required_size) {
        std::cerr << "env var path not found" << std::endl;
        return -1;
    }
    std::unique_ptr <char> buf{ new char[required_size] {} };
    ::getenv_s(&required_size, buf.get(), required_size, "path");
    std::string envPath(buf.get());
    auto paths = split(envPath, ";");
    for (const auto& t : paths) {
        std::cout << t << std::endl;
    }
}