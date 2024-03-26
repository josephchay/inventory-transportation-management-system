#include "SupplierBlock.h"
#include <sstream>

namespace blockchain {
    SupplierBlock::SupplierBlock(const int version, const std::string bits, int height, const std::string& previousHash, const SupplierInfo& info, int nonce, const std::string& currentHash)
            : Block(version, bits, height, previousHash, formatSupplierInfo(info), blockchain::enums::BlockType::SUPPLIER, nonce, currentHash), info(info) {
        // The constructor initializes the Block part with formatted supplier information
    }

    std::string SupplierBlock::formatSupplierInfo(const SupplierInfo& info) {
        std::ostringstream oss;
        oss << "ID: " << info.supplierId
            << " | Name: " << info.supplierName
            << " | Location: " << info.supplierLocation
            << " | Branch: " << info.supplierBranch;
        return oss.str();
    }

    SupplierInfo SupplierBlock::getInfo() const {
        return info;
    }
}
