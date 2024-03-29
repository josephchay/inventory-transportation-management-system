#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace utils {
    class Datetime {
    public:
        /**
         * @brief Format a timestamp.
         * Formats a timestamp to a string.
         *
         * @param time
         * @return
         */
        static std::string formatTimestamp(std::time_t time);
    };
} // namespace utils