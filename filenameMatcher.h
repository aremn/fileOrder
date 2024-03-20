#pragma once

#include <unordered_map>
#include <vector>
#include <string>

namespace std::filesystem {
    class directory_iterator;
}

class FilenameMatcher {
private: 
    std::unordered_map<std::string, int> filename_to_int; 
    std::vector<std::string> int_to_filename;

public: 
    FilenameMatcher(const std::string& directory);
    int filenameToNumber(const std::string& filename) const;
    std::string numberToFilename(int number) const;
};
