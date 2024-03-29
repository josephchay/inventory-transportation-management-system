#include "TransactionBlock.h"

namespace blockchain {
    TransactionBlock::TransactionBlock(const int version, const std::string bits, int height, const std::string& previousHash, TransactionInfo& info, int nonce, const std::string& currentHash, bool visible)
            : Block(version, bits, height, previousHash, info.toString(), blockchain::enums::BlockType::TRANSACTION, nonce, currentHash, visible), info(info) {
        // No additional initialization needed here
    }

    std::string TransactionInfo::toString() const {
        std::ostringstream oss;
        oss << "ID: " << transactionId
            << " | Total Fees (RM): " << totalFees
            << " | Commission Fees (RM) " << commissionFees
            << " | Retailer Per-Trip Credit Balance (RM): " << retailerPerTripCreditBalance
            << " | Annual Ordering Credit Balance (RM): " << annualOrderingCreditBalance
            << " | Payment Type: " << paymentType
            << " | Product Ordering Limit: " << productOrderingLimit;
        return oss.str();
    }

    TransactionInfo TransactionBlock::getInfo() const {
        return info;
    }
}
