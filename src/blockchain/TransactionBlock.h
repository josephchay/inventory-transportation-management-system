#pragma once

#include "Block.h"
#include <string>

namespace blockchain {
    struct TransactionInfo {
        int transactionId;
        std::string retailerPerTripCreditBalance;
        std::string annualOrderingCreditBalance;
        int paymentType; // options will be given to the user to select.
        int productOrderingLimit; // options will be given to the user to select.

        TransactionInfo() = default;
        TransactionInfo(const int& id, const std::string& retailerPerTripCreditBalance, const std::string& annualOrderingCreditBalance, int& paymentType, const int& productOrderingLimit)
                : transactionId(id), retailerPerTripCreditBalance(retailerPerTripCreditBalance), annualOrderingCreditBalance(annualOrderingCreditBalance), paymentType(paymentType), productOrderingLimit(productOrderingLimit) {}
    };

    class TransactionBlock : public Block {
    public:
        TransactionBlock(int blockNumber, const std::string& previousBlockHash, TransactionInfo& info);

        TransactionInfo getInfo() const;

    protected:
        TransactionInfo info;
        static std::string formatTransactionInfo(const TransactionInfo& info);
    };
}
