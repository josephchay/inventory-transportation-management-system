#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct TransactionInfo : public BlockInfo {
        int transactionId;
        std::string retailerPerTripCreditBalance;
        std::string annualOrderingCreditBalance;
        std::string paymentType;
        std::string productOrderingLimit;

        TransactionInfo() = default;
        TransactionInfo(const int& id, const std::string& retailerPerTripCreditBalance, const std::string& annualOrderingCreditBalance, std::string& paymentType, const std::string& productOrderingLimit)
                : transactionId(id), retailerPerTripCreditBalance(retailerPerTripCreditBalance), annualOrderingCreditBalance(annualOrderingCreditBalance), paymentType(paymentType), productOrderingLimit(productOrderingLimit) {}

        [[nodiscard]] std::string toString() const override;
    };

    class TransactionBlock : public Block {
    public:
        TransactionBlock(const int version, const std::string bits,int height, const std::string& previousHash, TransactionInfo& info, int nonce = 0, const std::string& currentHash = "", bool visible = true);

        TransactionInfo getInfo() const;

        [[nodiscard]] std::shared_ptr<Block> clone() const override {
            return std::make_shared<TransactionBlock>(*this);
        }

    protected:
        TransactionInfo info;
    };
}
