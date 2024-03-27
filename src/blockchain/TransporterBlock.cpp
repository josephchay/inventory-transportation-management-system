#include "TransporterBlock.h"

namespace blockchain {
    TransporterBlock::TransporterBlock(const int version, const std::string bits, int height, const std::string& previousHash, const TransporterInfo& info, int nonce, const std::string& currentHash, bool visible)
            : Block(version, bits, height, previousHash, info.toString(), blockchain::enums::BlockType::TRANSPORTER, nonce, currentHash, visible), info(info) {
        // No additional initialization needed here
    }

    std::string TransporterInfo::toString() const {
        std::ostringstream oss;
        oss << "ID: " << transporterId
            << " | Name: " << transporterName
            << " | Product Type: " << productType
            << " | Transportation Type: " << transportationType
            << " | Ordering Type: " << orderingType
            << " | Ordering Amount (Kg): " << orderingAmount;
        return oss.str();
    }

    TransporterInfo TransporterBlock::getInfo() const {
        return info;
    }
}
