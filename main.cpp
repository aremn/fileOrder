#include "filenameMatcher.h"
#include "dependencyProvider.h"
#include "orderProvider.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string directoryPath = "./test";

    // Инициализация и тестирование FilenameMatcher
    FilenameMatcher filenameMatcher(directoryPath);
    // Простой тест для FilenameMatcher
    std::cout << "Filename to ID mapping for 'a.h': " << filenameMatcher.filenameToNumber("a.h") << std::endl;

    // Инициализация и использование DependencyProvider
    DependencyProvider dependencyProvider(directoryPath, filenameMatcher);
    dependencyProvider.analyzeDependencies();

    // Вывод найденных зависимостей
    auto dependencies = dependencyProvider.getDependencies();
    std::cout << "Found dependencies:" << std::endl;
    for (const auto& [id, deps] : dependencies) {
        std::cout << "File " << filenameMatcher.numberToFilename(id) << " depends on: ";
        for (int dep : deps) {
            std::cout << filenameMatcher.numberToFilename(dep) << " ";
        }
        std::cout << std::endl;
    }

    // Использование OrderProvider для определения порядка обработки
    OrderProvider orderProvider(dependencies);
    auto order = orderProvider.provideOrder();
    std::cout << "\nProcessing order:" << std::endl;
    for (int id : order) {
        std::cout << filenameMatcher.numberToFilename(id) << std::endl;
    }

    return 0;
}
