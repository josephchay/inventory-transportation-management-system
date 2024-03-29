#pragma once

#include "../blockchain/SupplierBlock.h"
#include "../blockchain/TransporterBlock.h"
#include "../blockchain/TransactionBlock.h"
#include "../blockchain/enums/BlockAttribute.h"
#include "../blockchain/Chain.h"

namespace collection {
    class InputCollector {
    public:
        /**
         * @brief Collects username and password details from the user.
         *
         * @return
         */
        static std::pair<std::string, std::string> collectLoginDetails();

        /**
         * @brief Collects the all the header information for a Supplier variant Block.
         *
         * @param optionsFilePath
         * @return
         */
        static blockchain::SupplierInfo collectSupplierInfo(const std::string& optionsFilePath);

        /**
         * @brief Collects the all the header information for a Transporter variant Block.
         *
         * @param optionsFilePath
         * @return
         */
        static blockchain::TransporterInfo collectTransporterInfo(const std::string& optionsFilePath);

        /**
         * @brief Collects the all the header information for a Transaction variant Block.
         *
         * @param optionsFilePath
         * @param recordsFilePath
         * @return
         */
        static blockchain::TransactionInfo collectTransactionInfo(const std::string& optionsFilePath, const std::string& recordsFilePath);

        /**
         * @brief Collects the search criteria from the participant.
         * Prompts the participant to select a block's attribute to perform the operation by as well as the value to search for under that attribute.
         *
         * @param searchOptions
         * @param topic
         * @return
         */
        static std::pair<blockchain::enums::BlockAttribute, std::string> collectSearchCriteria(const std::vector<std::string>& searchOptions, const std::string& topic = "search");

        /**
         * @brief Collects the block manipulation criteria from the participant.
         * Where dynamic blockchain occurs here.
         * Allows the participant to either Soft Edit, Hard Edit, Soft Delete, Hard Delete, or mine any block as long as its visible.
         *
         * @param blockchain
         * @param redactedBlockchain
         * @param searchOptions
         */
        static void collectBlockManipulationCriteria(blockchain::Chain& blockchain, blockchain::Chain& redactedBlockchain, const std::vector<std::string>& searchOptions);
    };
}
