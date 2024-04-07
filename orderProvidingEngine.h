#include <iostream>
#include <string>
#include <unordered_set>
#include "filenameMatcher.h"
#include "dependencyProvider.h"
#include "orderProvider.h"

class OrderProvidingEngine {
private:
    const FilenameMatcher* matcher;
    std::unordered_map<int, std::vector<int>> dependencies;

    void displayDependency(int fileId, int level = 0) {
        std::string indent(level * 4, ' '); 
        if (level > 0) {
            std::cout << indent.substr(0, indent.size() - 2) << "|-> " << matcher->numberToFilename(fileId) << std::endl;
        } else {
            std::cout << matcher->numberToFilename(fileId) << std::endl;
        }

        if (dependencies.find(fileId) != dependencies.end()) {
            for (int depId : dependencies[fileId]) {
                displayDependency(depId, level + 1);
            }
        }
    }

public:
    void execute(std::istream& input, std::ostream& output) {
        std::string directoryPath;
        std::getline(input, directoryPath);

        FilenameMatcher localMatcher(directoryPath);
        matcher = &localMatcher;

        DependencyProvider dependencyProvider(directoryPath, *matcher);
        dependencyProvider.analyzeDependencies();

        dependencies = dependencyProvider.getDependencies();
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

        if(order.size() > 40) { 
            std::cout << "Sorry, graph is too big to visualize :(" << "\n";
        } else {
            displayDependency(order.back());
        }
        

        output << "\n";
        std::cout << "Order of Processing" << "\n";
        for (int id : order) {
            output << matcher->numberToFilename(id) << std::endl;
        }
    }
};