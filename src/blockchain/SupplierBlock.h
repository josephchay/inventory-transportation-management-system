#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct SupplierInfo : public BlockInfo {
        int supplierId; /** The ID of the supplier */
        std::string supplierName; /** The name of the supplier */
        std::string supplierLocation; /** The absolute location of the supplier */
        std::string supplierBranch; /** The branch of the supplier */
        std::string items; /** The items that the supplier provides in this particular block transaction */

        /**
         * @brief Default constructor for the SupplierInfo class
         */
        SupplierInfo() = default;

        /**
         * @brief Constructor for the SupplierInfo class
         *
         * @param id
         * @param name
         * @param location
         * @param branch
         * @param items
         */
        SupplierInfo(const int& id, const std::string& name, const std::string& location, const std::string& branch, const std::string& items)
                : supplierId(id), supplierName(name), supplierLocation(location), supplierBranch(branch), items(items) {}

        /**
         * @brief Convert the SupplierInfo object to a string
         * Overridden from the BlockInfo class
         *
         * @return
         */
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

        /**
         * @brief Provide a deep copy of the current block.
         *
         * @return
         */
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
