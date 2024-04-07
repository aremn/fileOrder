#include <fstream>
#include <regex>
#include <filesystem>
#include "filenameMatcher.h"
#include <unordered_map>
#include <cstdlib> 

class DependencyProvider { 
private:
    std::unordered_map<int, std::vector<int>> dependencies;
    const FilenameMatcher& filenameMatcher;
    std::string directory;

public: 
    DependencyProvider(const std::string& dir, const FilenameMatcher& matcher) : filenameMatcher(matcher), directory(dir)  {};

    const std::unordered_map<int, std::vector<int>> getDependencies() const { 
        return dependencies;
    }


    void processFile(const std::filesystem::path& filePath) {
    std::ifstream file(filePath);
    std::string line;
    std::regex includePattern(R"(#include\s+\"([^\"]+))"); 
    std::smatch match;

    int fileId = filenameMatcher.filenameToNumber(filePath.filename().string());

    if (fileId == -1) {
        std::cerr << "Warning: File " << filePath.filename() << " not found in filename mapping." << std::endl;
        return;
    }


    while (std::getline(file, line)) {
        if (std::regex_search(line, match, includePattern) && match.size() > 1) {
            std::string includedFilename = match[1].str();
            std::filesystem::path includedFilePath = filePath.parent_path() / includedFilename;

            if (!std::filesystem::exists(includedFilePath)) {
                std::cerr << "The file " << includedFilename << " included in " << filePath.filename() << " was not found; file processing is terminated." << std::endl;
                exit(1); 
            }

            int includedFileId = filenameMatcher.filenameToNumber(includedFilename);
            if (includedFileId != -1) {
                dependencies[fileId].push_back(includedFileId);
            }
        }
    }
}


    void analyzeDependencies() { 
    for(const auto& entry : std::filesystem::directory_iterator(directory)) { 
        if(entry.path().extension() == ".h") { 
            processFile(entry.path());
        }
    }
}   
};  



