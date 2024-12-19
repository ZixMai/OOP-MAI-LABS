#pragma once
#include <iostream>
#include "ILogger.h"

namespace Logger {
    class ConsoleLogger : public ILogger {
        std::ostream& os;
    public:
        ConsoleLogger() : os(std::cout) {};
        ConsoleLogger(const ConsoleLogger& other) = default;
        ConsoleLogger(ConsoleLogger&& other) noexcept = default;
        ConsoleLogger& operator=(const ConsoleLogger& other) = delete;
        ConsoleLogger& operator=(ConsoleLogger&& other) noexcept = delete;
        explicit ConsoleLogger(std::ostream& ostr, std::string name) : ILogger(std::move(name)), os(ostr) {};
        void log(const std::string& str) const override;
        ~ConsoleLogger() override = default;
    };

}