#include <unordered_map>
#include <vector>
#include <stack>
#include <iostream>

class OrderProvider {
private:
    std::unordered_map<int, std::vector<int>> dependencies;

public:
    OrderProvider(const std::unordered_map<int, std::vector<int>>& deps) : dependencies(deps) {}

    std::vector<int> provideOrder() {
        std::vector<int> order;
        std::stack<int> stack;
        std::unordered_map<int, bool> visited;
        std::unordered_map<int, bool> recStack;

        for (const auto& pair : dependencies) {
            if (!visited[pair.first]) {
                if (isCyclic(pair.first, visited, recStack, stack)) {
                    std::cout << "Cycle detected. Cannot perform topological sort." << std::endl;
                    return {};
                }
            }
        }

        while (!stack.empty()) {
            int fileId = stack.top();
            stack.pop();
            order.push_back(fileId);
        }

        std::reverse(order.begin(), order.end());
        return order;
    }

private:
    bool isCyclic(int v, std::unordered_map<int, bool>& visited, std::unordered_map<int, bool>& recStack, std::stack<int>& stack) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            for (int neighbor : dependencies[v]) {
                if (!visited[neighbor] && isCyclic(neighbor, visited, recStack, stack))
                    return true;
                else if (recStack[neighbor])
                    return true;
            }
        }

        recStack[v] = false;
        stack.push(v);
        return false;
    }
};
