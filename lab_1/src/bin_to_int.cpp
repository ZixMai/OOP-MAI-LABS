#include <cmath>
#include "bin_to_int.h"

int count_char_repeats(const std::string&custom_string, const char letter) {
    int amount = 0;
    for (const auto char_symbol : custom_string) {
        amount += static_cast<int>(char_symbol == letter);
    }
    return amount;
}

int from_bin_to_int(const std::string&binary_string) {
    return static_cast<int>(std::pow(2, count_char_repeats(binary_string, '1'))) - 1;
}