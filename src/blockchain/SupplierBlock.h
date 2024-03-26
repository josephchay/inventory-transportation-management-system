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
         * @param height
         * @param previousHash
         * @param info
         * @param nonce
         * @param currenHash
         */
        SupplierBlock(const int version, const std::string bits, int height, const std::string& previousHash, const SupplierInfo& info, int nonce = 0, const std::string& currenHash = "", bool visible = true);

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
