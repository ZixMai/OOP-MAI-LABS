#pragma once
#include <shared_mutex>
#include <string>
#include <stdexcept>
#include <utility>

namespace Logger {

    static std::shared_mutex loggerMutex;

    class ILogger {
        std::string name;
    public:
        ILogger() : name("Logger") {}
        explicit ILogger(std::string  name) : name(std::move(name)) {}
        virtual void log(const std::string& data) const = 0;
        virtual std::string getName() { return name; }
        bool operator==(const ILogger& other) const {
            return name == other.name;
        }
        virtual ~ILogger() = default;
    };

}