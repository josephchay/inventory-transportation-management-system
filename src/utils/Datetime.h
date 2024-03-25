#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace utils {
    class Datetime {
    public:
        static std::string formatTimestamp(std::time_t time);
    };
} // namespace utils