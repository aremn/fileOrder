#include <fstream>
#include <iostream>
#include <filesystem>

/// Сложные зависимости

void createFilesWithComplexDependencies(const std::string& directoryPath) {
    std::ofstream linear1(directoryPath + "/linear1.h");
    linear1 << "#pragma once\n#include \"linear2.h\"\n";
    linear1.close();

    std::ofstream linear2(directoryPath + "/linear2.h");
    linear2 << "#pragma once\n#include \"linear3.h\"\n";
    linear2.close();

    std::ofstream linear3(directoryPath + "/linear3.h");
    linear3 << "#pragma once\n// This file has no further includes\n";
    linear3.close();

    std::ofstream cycle1(directoryPath + "/cycle1.h");
    cycle1 << "#pragma once\n#include \"cycle2.h\"\n#include \"linear1.h\"\n"; 
    cycle1.close();

    std::ofstream cycle2(directoryPath + "/cycle2.h");
    cycle2 << "#pragma once\n#include \"cycle3.h\"\n";
    cycle2.close();

    std::ofstream cycle3(directoryPath + "/cycle3.h");
    cycle3 << "#pragma once\n#include \"cycle1.h\"\n"; 
    cycle3.close();

    std::cout << "Created files with complex dependencies including cycles and linear chains." << std::endl;
}

int main() {
    std::string directoryPath = "./test"; 

    std::filesystem::create_directory(directoryPath);

    createFilesWithComplexDependencies(directoryPath);

    return 0;
}
