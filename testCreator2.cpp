#include <fstream>
#include <iostream>
#include <filesystem>

/// Создает цикличные header'ы

void createFilesWithCyclicDependenciesAndMissingFile(const std::string& directoryPath) {
    std::ofstream file1(directoryPath + "/cycle1.h");
    file1 << "#pragma once\n#include \"cycle2.h\"\n";
    file1.close();

    std::ofstream file2(directoryPath + "/cycle2.h");
    file2 << "#pragma once\n#include \"cycle1.h\"\n#include \"missing.h\"\n"; 
    file2.close();

    std::cout << "Created files with cyclic dependencies and a reference to a missing file." << std::endl;
}

int main() {
    std::string directoryPath = "./test"; 

    std::filesystem::create_directory(directoryPath);

    createFilesWithCyclicDependenciesAndMissingFile(directoryPath);

    return 0;
}
