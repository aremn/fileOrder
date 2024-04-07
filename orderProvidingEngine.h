#include <iostream>
#include <string>
#include "filenameMatcher.h"
#include "dependencyProvider.h"
#include "orderProvider.h"

class OrderProvidingEngine {
public:
    void execute(std::istream& input, std::ostream& output) {
        std::string directoryPath;
        std::getline(input, directoryPath); 

        FilenameMatcher matcher(directoryPath); 
        DependencyProvider dependencyProvider(directoryPath, matcher); 
        dependencyProvider.analyzeDependencies(); 

        auto dependencies = dependencyProvider.getDependencies();
        if (dependencies.empty()) {
            output << "No dependencies found or error reading files." << std::endl;
            return;
        }

        OrderProvider orderProvider(dependencies);
        auto order = orderProvider.provideOrder(); 

        if (order.empty()) {
            output << "Circular include detected; file processing is terminated." << std::endl;
            return;
        }

        for (int id : order) {
            output << matcher.numberToFilename(id) << std::endl; 
        }
    }
};
