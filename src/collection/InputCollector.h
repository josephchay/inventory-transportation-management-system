#pragma once

#include "../blockchain/SupplierBlock.h"
#include "../blockchain/TransporterBlock.h"
#include "../blockchain/TransactionBlock.h"

namespace collection {
    class Prompt {
    public:
        static blockchain::SupplierInfo collectSupplierInfo(const std::string& optionsFilePath);
        static blockchain::TransporterInfo collectTransporterInfo(const std::string& optionsFilePath);
        static blockchain::TransactionInfo collectTransactionInfo(const std::string& optionsFilePath, const std::string& recordsFilePath);
    };
}
