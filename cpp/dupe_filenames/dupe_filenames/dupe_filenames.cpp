////////////////////////////////////////////////////////////////////////////////
// http://en.cppreference.com/w/cpp/filesystem
// https://docs.microsoft.com/en-us/cpp/standard-library/filesystem
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>
#include <experimental/filesystem>
#include <vector>
#include <map>

namespace fs = std::experimental::filesystem;

using FilesMap = std::map <std::wstring, std::vector <std::wstring>>;

int main() {
    const fs::path currentFolder{ "." };
    std::cout << "starting in : " << currentFolder << std::endl;

    FilesMap filesMap;

    fs::recursive_directory_iterator recurse_iter(currentFolder);

    for (auto& dir : recurse_iter) {
        // std::cout << dir << std::endl;
        const auto& type = dir.status().type();
        if (type == fs::file_type::regular) {
            CStringW filename = dir.path().filename().c_str();
            filename.MakeLower();
            std::wstring wfilenName = filename.GetBuffer();

            auto entry = filesMap.find(wfilenName);
            if (entry == filesMap.end()) {
                std::vector <std::wstring> paths;
                paths.push_back(dir.path());
                filesMap[wfilenName] = paths;
            }
            else {
                auto paths = entry;
                paths->second.push_back(dir.path());
            }
        }
    }

    std::wcout << L"dupes:" << std::endl;
    for (auto filename : filesMap) {
        if (filename.second.size() > 1) {
            std::wcout << filename.first << std::endl;
            auto paths = filename.second;
            for (auto path : paths) {
                std::wcout << L"  " << path << std::endl;
            }
        }
    }
}