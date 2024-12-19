#include <iostream>

#include "src/seven.h"

int main(int argc, char **argv) {
    std::string v1, v2;

    std::cout << "Enter numbers" << std::endl;
    std::cin >> v1 >> v2;

    auto h1 = seven::Seven(v1);
    const auto h2 = seven::Seven(v2);

    std::cout << (h1 + h2).get_value();
}