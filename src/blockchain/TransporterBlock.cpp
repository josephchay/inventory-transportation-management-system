#include "TransporterBlock.h"

namespace blockchain {
    TransporterBlock::TransporterBlock(int number, const std::string& previousHash, const TransporterInfo& info, const std::string& currentHash)
            : Block(number, previousHash, formatTransporterInfo(info), "Transporter", currentHash), info(info) {
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
