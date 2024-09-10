#include <iostream>

#include "./src/bin_to_int.h"

int main() {
  std::string binary_string;
  std::cin >> binary_string;
  std::cout << from_bin_to_int(binary_string) << std::endl;
}
