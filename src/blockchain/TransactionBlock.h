#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct TransactionInfo {
        int transactionId;
        std::string retailerPerTripCreditBalance;
        std::string annualOrderingCreditBalance;
        std::string paymentType;
        std::string productOrderingLimit;

        TransactionInfo() = default;
        TransactionInfo(const int& id, const std::string& retailerPerTripCreditBalance, const std::string& annualOrderingCreditBalance, std::string& paymentType, const std::string& productOrderingLimit)
                : transactionId(id), retailerPerTripCreditBalance(retailerPerTripCreditBalance), annualOrderingCreditBalance(annualOrderingCreditBalance), paymentType(paymentType), productOrderingLimit(productOrderingLimit) {}
    };

    class TransactionBlock : public Block {
    public:
        TransactionBlock(const int version, const std::string bits,int height, const std::string& previousHash, TransactionInfo& info, int nonce = 0, const std::string& currentHash = "");

        TransactionInfo getInfo() const;

    protected:
        TransactionInfo info;
        static std::string formatTransactionInfo(const TransactionInfo& info);
    };
}
