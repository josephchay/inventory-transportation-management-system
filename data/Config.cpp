#include "Config.h"

namespace data {
    const int Config::VERSION = 1;
    const std::string Config::RECORDS_BLOCKCHAIN_FILE_PATH = R"(../data/records/chain.txt)";
    const std::string Config::OPTIONS_SUPPLIER_FILE_PATH = R"(../data/options/suppliers.txt)";
    const std::string Config::OPTIONS_TRANSPORTER_FILE_PATH = R"(../data/options/transporters.txt)";
    const std::string Config::OPTIONS_TRANSACTION_FILE_PATH = R"(../data/options/transactions.txt)";
}
