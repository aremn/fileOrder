#include "orderProvidingEngine.h"
#include <iostream>
#include <sstream>

int main() {
    OrderProvidingEngine engine;

    std::istringstream input("./test");
    std::ostream& output = std::cout;

    engine.execute(input, output);

    return 0;
}
