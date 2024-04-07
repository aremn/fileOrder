#include <fstream>
#include <iostream>
#include <filesystem>

/// Создает n зависимых друг от друга header'ов, кроме последнего

int main() {
    std::string directoryPath = "./test"; 
    int numberOfFiles = 100; 

    std::filesystem::create_directory(directoryPath);

    for (int i = 1; i <= numberOfFiles; ++i) {
        std::ofstream file(directoryPath + "/header" + std::to_string(i) + ".h");

        if (!file) {
            std::cerr << "Failed to create file: header" << i << ".h" << std::endl;
            return 1;
        }

        if (i < numberOfFiles) { 
            file << "#pragma once\n#include \"header" << (i + 1) << ".h\"\n";
        } else {
            file << "#pragma once\n// This is the last file in the dependency chain\n";
        }

        file.close();
    }

    std::cout << "Successfully created " << numberOfFiles << " header files with linear dependencies." << std::endl;

    return 0;
}
