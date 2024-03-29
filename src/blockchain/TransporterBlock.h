#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct TransporterInfo : public BlockInfo {
        int transporterId; /** Unique identifier for the transporter */
        std::string transporterName; /** Name of the transporter */
        std::string productType; /** Type of product the transporter will transport */
        std::string transportationType; /** Type of transportation the transporter will use */
        std::string orderingType; /** Type of ordering the transporter used */
        double orderingAmount; /** Amount of product ordered in kilograms */

        /**
         * @brief Default constructor for the TransporterInfo class
         */
        TransporterInfo() = default;

        /**
         * @brief Constructor for the TransporterInfo class
         *
         * @param id
         * @param name
         * @param productType
         * @param transportationType
         * @param orderingType
         * @param orderingAmount
         */
        TransporterInfo(const int& id, const std::string& name, const std::string& productType, const std::string& transportationType, const std::string& orderingType, const double& orderingAmount)
                : transporterId(id), transporterName(name), productType(productType), transportationType(transportationType), orderingType(orderingType), orderingAmount(orderingAmount) {}

        /**
         * @brief Convert the TransporterInfo object to a string
         * Overridden from the BlockInfo class
         *
         * @return
         */
        [[nodiscard]] std::string toString() const override;
    };

    class TransporterBlock : public Block {
    public:
        /**
         * Constructor for the TransporterBlock class
         *
         * @param version
         * @param bits
         * @param height
         * @param previousHash
         * @param info
         * @param nonce
         * @param currentHash
         * @param visible
         */
        TransporterBlock(const int version, const std::string bits, int height, const std::string& previousHash, const TransporterInfo& info, int nonce = 0, const std::string& currentHash = "", bool visible = true);

        /**
         * @brief Get the transporter information.
         *
         * @return
         */
        TransporterInfo getInfo() const;

        /**
         * @brief Make a deep copy the TransporterBlock object
         *
         * @return
         */
        [[nodiscard]] std::shared_ptr<Block> clone() const override {
            return std::make_shared<TransporterBlock>(*this);
        }

    private:
        TransporterInfo info; /** header information about the transporter */
    };
}
