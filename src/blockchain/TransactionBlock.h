#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct TransactionInfo : public BlockInfo {
        int transactionId; /** The ID of the transaction */
        std::string totalFees; /** The total fees of the transaction */
        std::string retailerPerTripCreditBalance; /** The retailer's credit balance per trip */
        std::string annualOrderingCreditBalance; /** The retailer's annual ordering credit balance */
        std::string paymentType; /** The payment type used for the transaction */
        std::string productOrderingLimit; /** The limit of the product ordering */
        std::string commissionFees; /** The commission fees of the transaction */

        /**
         * @brief Default constructor for the TransactionInfo class
         */
        TransactionInfo() = default;

        /**
         * @brief Constructor for the TransactionInfo class
         *
         * @param id
         * @param totalFees
         * @param commisionFees
         * @param retailerPerTripCreditBalance
         * @param annualOrderingCreditBalance
         * @param paymentType
         * @param productOrderingLimit
         */
        TransactionInfo(const int& id, const std::string totalFees, const std::string commisionFees, const std::string& retailerPerTripCreditBalance, const std::string& annualOrderingCreditBalance, std::string& paymentType, const std::string& productOrderingLimit)
                : transactionId(id), totalFees(totalFees), commissionFees(commisionFees), retailerPerTripCreditBalance(retailerPerTripCreditBalance), annualOrderingCreditBalance(annualOrderingCreditBalance), paymentType(paymentType), productOrderingLimit(productOrderingLimit) {}

        /**
         * @brief Convert the TransactionInfo object to a string
         * Overridden from the BlockInfo class
         *
         * @return
         */
        [[nodiscard]] std::string toString() const override;
    };

    class TransactionBlock : public Block {
    public:
        /**
         * Constructor for the TransactionBlock class
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
        TransactionBlock(const int version, const std::string bits,int height, const std::string& previousHash, TransactionInfo& info, int nonce = 0, const std::string& currentHash = "", bool visible = true);

        /**
         * @brief Get the transaction information.
         *
         * @return
         */
        TransactionInfo getInfo() const;

        /**
         * @brief Clone the TransactionBlock object
         *
         * @return
         */
        [[nodiscard]] std::shared_ptr<Block> clone() const override {
            return std::make_shared<TransactionBlock>(*this);
        }

    protected:
        TransactionInfo info; /** The header information of the Transaction */
    };
}
