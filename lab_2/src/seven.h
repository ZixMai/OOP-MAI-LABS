#pragma once
#include <initializer_list>
#include <stdexcept>
#include <string>

namespace seven {
    class Seven {
    public:
        Seven();
        explicit Seven(const std::string& string);
        Seven(const std::initializer_list<unsigned char> &t);
        Seven(const Seven& seven);
        Seven& operator=(const Seven& other);
        Seven(Seven&& seven) noexcept ;
        Seven& operator=(Seven&& other)  noexcept ;

        unsigned char * get_value() const;

        Seven operator+(const Seven& other) const;
        Seven operator-(const Seven& other) const;
        bool operator<(const Seven& other) const;
        bool operator>(const Seven& other) const;
        bool operator==(const Seven& other) const;
        bool operator!=(const Seven& other) const;
        Seven& operator+=(const Seven& other);
        Seven& operator-=(const Seven& other);

        ~Seven() noexcept;

    private:
        unsigned char* value;
        size_t size;

        explicit Seven(size_t size);

        static void swap(Seven& num1, Seven& num2) noexcept;
    };

}