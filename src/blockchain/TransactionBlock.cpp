#include "TransactionBlock.h"

namespace blockchain {
    TransactionBlock::TransactionBlock(int number, const std::string& previousHash, TransactionInfo& info, const std::string& currentHash)
            : Block(number, previousHash, formatTransactionInfo(info), "Transaction", currentHash), info(info) {
        // No additional initialization needed here
    }

    std::string TransactionBlock::formatTransactionInfo(const TransactionInfo& info) {
        std::ostringstream oss;
        oss << "ID: " << info.transactionId
            << " | Retailer Per-Trip Credit Balance: " << info.retailerPerTripCreditBalance
            << " | Annual Ordering Credit Balance: " << info.annualOrderingCreditBalance
            << " | Payment Type: " << info.paymentType
            << " | Product Ordering Limit: " << info.productOrderingLimit;
        return oss.str();
    }

    TransactionInfo TransactionBlock::getInfo() const {
        return info;
    }
}
