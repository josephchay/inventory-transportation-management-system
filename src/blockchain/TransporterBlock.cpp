#include "TransporterBlock.h"

namespace blockchain {
    TransporterBlock::TransporterBlock(const int version, const std::string bits, int height, const std::string& previousHash, const TransporterInfo& info, int nonce, const std::string& currentHash)
            : Block(version, bits, height, previousHash, formatTransporterInfo(info), "Transporter", nonce, currentHash), info(info) {
        // No additional initialization needed here
    }

    std::string TransporterBlock::formatTransporterInfo(const TransporterInfo& info) {
        std::ostringstream oss;
        oss << "ID: " << info.transporterId
            << " | Name: " << info.transporterName
            << " | Product Type: " << info.productType
            << " | Transportation Type: " << info.transportationType
            << " | Ordering Type: " << info.orderingType
            << " | Ordering Amount (Kg): " << info.orderingAmount;
        return oss.str();
    }

    TransporterInfo TransporterBlock::getInfo() const {
        return info;
    }
}
