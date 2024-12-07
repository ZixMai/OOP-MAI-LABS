#pragma once
#include <fstream>
#include <utility>
#include "ILogger.h"
namespace Logger {

    class FileLogger : public ILogger {
        std::string filename;

    public:
        FileLogger() : ILogger(), filename("logs.txt") {}
        FileLogger(const FileLogger& other) = default;
        FileLogger(FileLogger&& other) noexcept = default;
        FileLogger& operator=(const FileLogger& other) = default;
        FileLogger& operator=(FileLogger&& other) noexcept;
        FileLogger(std::string  filename, std::string name) : ILogger(std::move(name)), filename(std::move(filename)) {}
        void log(const std::string& str) const override;
        ~FileLogger() override = default;
    };

}