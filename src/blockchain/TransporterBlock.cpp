#include "TransporterBlock.h"

namespace blockchain {
    TransporterBlock::TransporterBlock(int blockNumber, const std::string& previousBlockHash, const TransporterInfo& info)
            : Block(blockNumber, previousBlockHash, formatTransporterInfo(info), "Transporter"), info(info) {
        // No additional initialization needed here
    }

    std::string TransporterBlock::formatTransporterInfo(const TransporterInfo& info) {
        std::ostringstream oss;
        oss << "ID: " << info.transporterId
            << " | Name: " << info.transporterName
            << " | Product Type: " << info.productType
            << " | Ordering Type: " << info.orderingType
            << " | Ordering Amount (Kg): " << info.orderingAmount;
        return oss.str();
    }

    TransporterInfo TransporterBlock::getInfo() const {
        return info;
    }
}
