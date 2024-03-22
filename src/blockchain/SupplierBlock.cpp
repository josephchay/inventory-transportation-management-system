#include "SupplierBlock.h"
#include <sstream>

namespace blockchain {
    SupplierBlock::SupplierBlock(int blockNumber, const std::string& previousBlockHash, const SupplierInfo& info)
            : Block(blockNumber, previousBlockHash, formatSupplierInfo(info), "Supplier"), info(info) {
        // The constructor initializes the Block part with formatted supplier information
    }

    std::string SupplierBlock::formatSupplierInfo(const SupplierInfo& info) {
        std::ostringstream oss;
        oss << "Id: " << info.supplierId
            << " | Name: " << info.supplierName
            << " | Location: " << info.supplierLocation
            << " | Branch: " << info.supplierBranch;
        return oss.str();
    }

    SupplierInfo SupplierBlock::getInfo() const {
        return info;
    }
}
