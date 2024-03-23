#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct SupplierInfo {
        int supplierId;
        std::string supplierName;
        std::string supplierLocation;
        std::string supplierBranch;

        SupplierInfo() = default;
        SupplierInfo(const int& id, const std::string& name, const std::string& location, const std::string& branch)
                : supplierId(id), supplierName(name), supplierLocation(location), supplierBranch(branch) {}
    };

    class SupplierBlock : public Block {
    public:
        /**
         * @brief Construct a new Supplier Block object
         *
         * @param number
         * @param previousHash
         * @param info
         */
        SupplierBlock(int number, const std::string& previousHash, const SupplierInfo& info, const std::string& currenHash = "");

        /**
         * @brief Get the supplier information.
         *
         * @return SupplierInfo
         */
        SupplierInfo getInfo() const;

    private:
        /**
         * This field holds the raw supplier information.
         */
        SupplierInfo info;

        static std::string formatSupplierInfo(const SupplierInfo& info);
    };
}
