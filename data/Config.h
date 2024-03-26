#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace data {
    class Config {
    public:
        static const int VERSION;
        static const std::string RECORDS_BLOCKCHAIN_FILE_PATH;
        static const std::string OPTIONS_SUPPLIER_FILE_PATH;
        static const std::string OPTIONS_TRANSPORTER_FILE_PATH;
        static const std::string OPTIONS_TRANSACTION_FILE_PATH;
    };
} // namespace blockchain

#endif // CONFIG_H
