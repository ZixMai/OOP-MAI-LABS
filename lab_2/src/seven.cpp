#include "seven.h"
#include <stdexcept>
#include <algorithm>
#include <format>
#include <cmath>

namespace  {
    const unsigned short base = 7;
    const unsigned char chars[] = { '0', '1', '2', '3', '4', '5', '6' };

    void set_char(unsigned char * buffer, const unsigned char character, const size_t index, const size_t buffer_size) {
        if (std::find(std::begin(chars), std::end(chars), character) == std::end(chars)) {
            throw std::out_of_range(std::format("Number {} is wrong for base 7", character));
        }
        if (index >= buffer_size) {
            throw std::out_of_range(std::format("Received value went outside of number bounds {}", index));
        }
        buffer[index] = character;
    }

    std::string lpad(const unsigned char *const src, size_t srcSize, size_t targetSize) {
        auto padding = targetSize - srcSize;
        std::string padded(targetSize, ' ');

        for (size_t i = 0; i < targetSize; ++i){
            if (i < padding){
                padded[i] = '0';
                continue;
            }
            padded[i] = src[i - padding];
        }

        return padded;
    }

    std::string trim(std::string input) {
        auto start{0};
        while (input[start] == '0') { ++start; }

        std::string trimmed(input.length() - start, ' ');

        for (auto i = 0; i < input.length(); ++i){
            trimmed[i] = input[i + start];
        }

        return trimmed;
    }

    short get_int(const unsigned char character) {
        return character - '0';
    }
}

namespace seven {
    Seven::Seven(): value(nullptr), size(0) {}

    Seven::Seven(const size_t size) : size(size), value(new unsigned char[size + 1]) {
        this->value[this->size] = '\0';
    }

    Seven::Seven(const std::string& str) : Seven(str.length()) {
        for (size_t i = 0; i < this->size; ++i) {
            set_char(this->value, str[i], i, this->size);
        }
    }

    Seven::Seven(const std::initializer_list<unsigned char> &values) : Seven(values.size()) {
        size_t idx {0};

        for (const auto& val : values) {
            set_char(this->value, val, idx++, this->size);
        }
    }

    Seven::Seven(const Seven &other) : Seven(other.size) {
        for (size_t i = 0; i < other.size; ++i) {
            set_char(this->value, other.value[i], i, this->size);
        }
    }

    Seven::Seven(Seven &&other) noexcept {
        swap(*this, other);
    }

    unsigned char * Seven::get_value() const {
        if (this->size == 0) return nullptr;
        return this->value;
    }

    void Seven::swap(Seven &num1, Seven &num2) noexcept {
        num1.value = num2.value;
        num1.size = num2.size;

        num2.value = nullptr;
    }

    Seven Seven::operator+(const Seven &other) const {
        unsigned short buff {0};

        if (this->size > other.size) return other + *this;

        if (this->size == 0) return other;

        const size_t new_size = other.size;
        auto sum_result = lpad(this->value, this->size, new_size);

        for (int i = static_cast<int>(new_size) - 1; i >= 0; --i) {
            short left_digit = get_int(sum_result[i]);
            short right_digit = get_int(other.value[i]);
            short temp_sum = left_digit + right_digit + buff;
            buff = temp_sum / base;
            sum_result[i] = chars[temp_sum % base];
        }

        if (buff != 0) sum_result = std::format("{}{}", buff, sum_result);

        return Seven(sum_result);
    }

    Seven Seven::operator-(const Seven &other) const {
        unsigned short borrow {0};

        if (other > *this) throw std::invalid_argument("Result of subtraction is negative");

        const size_t new_size = this->size;
        auto diff_result = lpad(other.value, other.size, new_size);

        for (int i = static_cast<int>(new_size) - 1; i >= 0; --i) {
            short left_digit = get_int(this->value[i]);
            short right_digit = get_int(diff_result[i]);
            short temp_diff = left_digit - right_digit - borrow;

            if (temp_diff < 0) {
                temp_diff += base;
                borrow = 1;
            } else {
                borrow = 0;
            }
            diff_result[i] = chars[temp_diff];
        }

        return Seven(trim(diff_result));
    }


    bool Seven::operator<(const Seven &other) const {
        if (this->size != other.size) return this->size < other.size;
        if (this->size == 0) return false;

        for (size_t i = 0; i <= this->size; ++i) {
            short left_digit = get_int(this->value[i]), right_digit = get_int(other.value[i]);

            if (left_digit == right_digit) continue;

            return left_digit < right_digit;
        }

        return false;
    }

    bool Seven::operator>(const Seven &other) const {
        if (this->size != other.size) return this->size > other.size;
        if (this->size == 0) return false;

        for (size_t i = 0; i <= this->size; ++i) {
            short left_digit = get_int(this->value[i]), right_digit = get_int(other.value[i]);

            if (left_digit == right_digit) continue;

            return left_digit > right_digit;
        }

        return false;
    }

    bool Seven::operator==(const Seven &other) const {
        if (this->size != other.size) return false;
        for (size_t i = 0; i < this->size; ++i) {
            if (this->value[i] != other.value[i]) return false;
        }
        return true;
    }

    Seven& Seven::operator+=(const Seven &other) {
        auto sum_result = *this + other;
        swap(*this, sum_result);
        return *this;
    }

    Seven& Seven::operator-=(const Seven &other) {
        auto diff_result = *this - other;
        swap(*this, diff_result);
        return *this;
    }

    Seven &Seven::operator=(const Seven &other) {
        auto copy_rhs = Seven(other);
        swap(*this, copy_rhs);
        return *this;
    }

    Seven &Seven::operator=(Seven &&other) noexcept {
        swap(*this, other);
        return *this;
    }

    bool Seven::operator!=(const Seven &other) const {
        return !(*this == other);
    }

    Seven::~Seven() noexcept {
        delete[] this->value;
    }
}
