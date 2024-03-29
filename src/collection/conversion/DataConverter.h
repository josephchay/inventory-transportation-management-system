#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include "../../blockchain/SupplierBlock.h"
#include "../../blockchain/TransactionBlock.h"
#include "../../blockchain/TransporterBlock.h"
#include <string>

namespace conversion {
    class DataConverter {
    public:
        /**
         * @brief Convert given values into a SupplierBlock object
         *
         * @param version
         * @param bits
         * @param height
         * @param nonce
         * @param currentHash
         * @param previousHash
         * @param data
         * @param visible
         * @return
         */
        static blockchain::SupplierBlock convertToSupplierBlock(int version, const std::string bits, int height, int nonce, const std::string& currentHash, const std::string& previousHash, const std::string& data, bool visible);

        /**
         * @brief Convert given values into a TransporterBlock object
         *
         * @param version
         * @param bits
         * @param height
         * @param nonce
         * @param currentHash
         * @param previousHash
         * @param data
         * @param visible
         * @return
         */
        static blockchain::TransporterBlock convertToTransporterBlock(int version, const std::string bits, int height, int nonce, const std::string& currentHash, const std::string& previousHash, const std::string& data, bool visible);

        /**
         * @brief Convert given values into a TransactionBlock object
         *
         * @param version
         * @param bits
         * @param height
         * @param nonce
         * @param currentHash
         * @param previousHash
         * @param data
         * @param visible
         * @return
         */
        static blockchain::TransactionBlock convertToTransactionBlock(int version, const std::string bits, int height, int nonce, const std::string& currentHash, const std::string& previousHash, const std::string& data, bool visible);
    };
}

#endif // DATACONVERTER_H
