#include "TransactionBlock.h"

namespace blockchain {
    TransactionBlock::TransactionBlock(const int version, const std::string bits, int height, const std::string& previousHash, TransactionInfo& info, int nonce, const std::string& currentHash)
            : Block(version, bits, height, previousHash, formatTransactionInfo(info), blockchain::enums::BlockType::TRANSACTION, nonce, currentHash), info(info) {
        // No additional initialization needed here
    }

    std::string TransactionBlock::formatTransactionInfo(const TransactionInfo& info) {
        std::ostringstream oss;
        oss << "ID: " << info.transactionId
            << " | Retailer Per-Trip Credit Balance (RM): " << info.retailerPerTripCreditBalance
            << " | Annual Ordering Credit Balance (RM): " << info.annualOrderingCreditBalance
            << " | Payment Type: " << info.paymentType
            << " | Product Ordering Limit: " << info.productOrderingLimit;
        return oss.str();
    }

    TransactionInfo TransactionBlock::getInfo() const {
        return info;
    }
}
