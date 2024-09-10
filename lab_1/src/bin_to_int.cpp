#include <cmath>
#include <iostream>

int count_char_repeats(const std::string&custom_string, const char letter) {
    int amount = 0;
    for (const auto char_symbol : custom_string) {
        if (char_symbol == letter) {
            ++amount;
        }
    }
    return amount;
}

int from_bin_to_int(const std::string&binary_string) {
    const int answer = static_cast<int>(std::pow(2, count_char_repeats(binary_string, '1'))) - 1;
    return answer;
}