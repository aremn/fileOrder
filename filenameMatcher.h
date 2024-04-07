#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>


class FilenameMatcher {
private: 
    std::unordered_map<std::string, int> filename_to_int; 
    std::vector<std::string> int_to_filename;

public: 
    
    FilenameMatcher(const std::string& directory) {
        int id = 0;
        auto iterator = std::filesystem::directory_iterator(directory);

        for(const auto& i : iterator) {
            if(i.path().extension() == ".h") {
                std::string filename = i.path().filename().string();
                filename_to_int[filename] = id;
                int_to_filename.push_back(filename);
                ++id;
            }
        }
    }

    int filenameToNumber(const std::string& filename) const {
        auto it = filename_to_int.find(filename);
        if (it != filename_to_int.end()) {
            return it->second;
        }
        return -1;
    }
    
    std::string numberToFilename(int number) const {
        if(number >= 0 && number < static_cast<int>(int_to_filename.size())) {
            return int_to_filename[number];
        }
        return "";
    }

};

