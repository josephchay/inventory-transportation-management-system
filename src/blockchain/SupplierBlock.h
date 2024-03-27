#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct SupplierInfo : public BlockInfo {
        int supplierId;
        std::string supplierName;
        std::string supplierLocation;
        std::string supplierBranch;

        SupplierInfo() = default;
        SupplierInfo(const int& id, const std::string& name, const std::string& location, const std::string& branch)
                : supplierId(id), supplierName(name), supplierLocation(location), supplierBranch(branch) {}

        [[nodiscard]] std::string toString() const override;
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

        [[nodiscard]] std::shared_ptr<Block> clone() const override {
            return std::make_shared<SupplierBlock>(*this);
        }

    private:
        /**
         * This field holds the raw supplier information.
         */
        SupplierInfo info;
    };
}
