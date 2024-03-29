#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace data {
    class Config {
    public:
        static const int VERSION; /** The version of the blockchain */
        static const std::string RECORDS_BLOCKCHAIN_FILE_PATH; /** The path to the blockchain file */
        static const std::string OPTIONS_SUPPLIER_FILE_PATH; /** The path to the supplier options file */
        static const std::string OPTIONS_TRANSPORTER_FILE_PATH; /** The path to the transporter options file */
        static const std::string OPTIONS_TRANSACTION_FILE_PATH; /** The path to the transaction options file */
        static const std::string PARTICIPANTS_FILE_PATH; /** The path to the participants file */
    };
} // namespace blockchain

#endif // CONFIG_H
