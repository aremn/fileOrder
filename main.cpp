#include "filenameMatcher.h"
#include "dependencyProvider.h"
#include <iostream>

int main() {
    std::string testDirectory = "/home/aremn/projects/test"; 

    FilenameMatcher filenameMatcher(testDirectory);
    std::cout << "Testing FilenameMatcher:" << std::endl;
    std::cout << "ID for main.h: " << filenameMatcher.filenameToNumber("main.h") << std::endl;
    std::cout << "Filename for ID 0: " << filenameMatcher.numberToFilename(0) << std::endl;

    DependencyProvider dependencyProvider(testDirectory, filenameMatcher);
    dependencyProvider.analyzeDependencies();

    std::cout << "\nDependencies found:" << std::endl;
    for (const auto& [fileId, dependencies] : dependencyProvider.getDependencies()) {
        std::cout << filenameMatcher.numberToFilename(fileId) << " depends on: ";
        for (int depId : dependencies) {
            std::cout << filenameMatcher.numberToFilename(depId) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
