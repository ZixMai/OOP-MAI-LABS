#include "console_logger.h"

namespace Logger {
    void ConsoleLogger::log(const std::string &str) const {
        os << str << std::endl;
    }
}