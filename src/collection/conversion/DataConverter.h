#ifndef DATACONVERSION_H
#define DATACONVERSION_H

#include "../../blockchain/SupplierBlock.h"
#include "../../blockchain/TransactionBlock.h"
#include "../../blockchain/TransporterBlock.h"
#include <string>

namespace conversion {
    class DataConverter {
    public:
        static blockchain::SupplierBlock convertToSupplierBlock(int number, const std::string& currentHash, const std::string& previousHash, const std::string& data);
        static blockchain::TransporterBlock convertToTransporterBlock(int number, const std::string& currentHash, const std::string& previousHash, const std::string& data);
        static blockchain::TransactionBlock convertToTransactionBlock(int number, const std::string& currentHash, const std::string& previousHash, const std::string& data);
    };
}

#endif // DATACONVERSION_H
