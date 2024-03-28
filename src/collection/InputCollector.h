#pragma once

#include "../blockchain/SupplierBlock.h"
#include "../blockchain/TransporterBlock.h"
#include "../blockchain/TransactionBlock.h"
#include "../blockchain/enums/BlockAttribute.h"
#include "../blockchain/Chain.h"

namespace collection {
    class Prompt {
    public:
        static std::pair<std::string, std::string> collectLoginDetails();
        static blockchain::SupplierInfo collectSupplierInfo(const std::string& optionsFilePath);
        static blockchain::TransporterInfo collectTransporterInfo(const std::string& optionsFilePath);
        static blockchain::TransactionInfo collectTransactionInfo(const std::string& optionsFilePath, const std::string& recordsFilePath);
        static std::pair<blockchain::enums::BlockAttribute, std::string> collectSearchCriteria(const std::vector<std::string>& searchOptions, const std::string& topic = "search");
        static void collectBlockManipulationCriteria(blockchain::Chain& blockchain, blockchain::Chain& redactedBlockchain, const std::vector<std::string>& searchOptions);
    };
}
