#include "SupplierBlock.h"
#include <sstream>

namespace blockchain {
    SupplierBlock::SupplierBlock(const int version, const std::string bits, int height, const std::string& previousHash, const SupplierInfo& info, int nonce, const std::string& currentHash, bool visible)
            : Block(version, bits, height, previousHash, info.toString(), blockchain::enums::BlockType::SUPPLIER, nonce, currentHash, visible), info(info) {
        // The constructor initializes the Block part with formatted supplier information
    }

    std::string SupplierInfo::toString() const {
        std::ostringstream oss;
        oss << "ID: " << supplierId
            << " | Name: " << supplierName
            << " | Location: " << supplierLocation
            << " | Branch: " << supplierBranch;
        return oss.str();
    }

    SupplierInfo SupplierBlock::getInfo() const {
        return info;
    }
}
