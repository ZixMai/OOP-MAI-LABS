#include "console_logger.h"

namespace Logger {
    void ConsoleLogger::log(const std::string &str) const {
        std::shared_lock lock(loggerMutex);
        os << str << std::endl;
    }
}