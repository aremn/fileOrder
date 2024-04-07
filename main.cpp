#include "orderProvidingEngine.h"
#include <iostream>
#include <filesystem>
#include <sstream>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <directory_path>\n"
              << "Options:\n"
              << "  -h, --help       Show this help message\n\n"
              << "Example:\n"
              << "  " << programName << " ./project_directory\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2 || std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        printUsage(argv[0]);
        return 0; 
    }

    std::string directoryPath = argv[1];
    
    if (!std::filesystem::exists(directoryPath) || !std::filesystem::is_directory(directoryPath)) {
        std::cerr << "Error: The specified path does not exist or is not a directory." << std::endl;
        return 1;
    }

    OrderProvidingEngine engine;
    std::istringstream inputStream(directoryPath);
    std::ostream& output = std::cout;

    engine.execute(inputStream, output);

    return 0;
}
