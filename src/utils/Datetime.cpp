#include "Datetime.h"

namespace utils {
    std::string Datetime::formatTimestamp(std::time_t time) {
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
} // namespace utils