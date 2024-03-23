#include "SupplierBlock.h"
#include <sstream>

namespace blockchain {
    SupplierBlock::SupplierBlock(int number, const std::string& previousHash, const SupplierInfo& info, const std::string& currentHash)
            : Block(number, previousHash, formatSupplierInfo(info), "Supplier", currentHash), info(info) {
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
