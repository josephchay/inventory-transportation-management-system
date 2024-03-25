#include "SupplierBlock.h"
#include <sstream>

namespace blockchain {
    SupplierBlock::SupplierBlock(int height, const std::string& previousHash, const SupplierInfo& info, int nonce, const std::string& currentHash)
            : Block(height, previousHash, formatSupplierInfo(info), "Supplier", nonce, currentHash), info(info) {
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
