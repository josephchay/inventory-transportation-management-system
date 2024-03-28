#include "../blockchain/SupplierBlock.h"
#include "InputCollector.h"
#include "validator/InputValidator.h"
#include "../filesystem/FileReader.h"
#include "../filesystem/FileWriter.h"
#include "../utils/Structures.h"
#include "../../data/Config.h"
#include <string>

namespace collection {
    static std::string validateAndEditOptionsField(const std::string& fieldName, const std::string& currentValue, const std::string& optionsFilePath, int row, int column) {
        while (true) { // Loop indefinitely until a return statement is executed
            bool confirmed = validation::InputValidator::validateConfirmValue(fieldName, currentValue);
            if (confirmed) {
                return currentValue; // User confirmed the value, return it and exit the loop
            } else {
                bool editAction = validation::InputValidator::validateConfirmValue("edit " + fieldName);
                if (editAction) {
                    std::string newValue = validation::InputValidator::validateString(fieldName);
                    filesystem::FileWriter::modifyCell(optionsFilePath, row, column, newValue);
                    return newValue; // User edited the value, return the new value and exit the loop
                }
                // If editAction is false, the loop will continue, effectively restarting the process
            }
        }
    }

    std::pair<std::string, std::string> Prompt::collectLoginDetails() {
        std::string username = validation::InputValidator::validateString("username");
        std::string password = validation::InputValidator::validateString("password");

        return std::make_pair(username, password);
    }

    blockchain::SupplierInfo Prompt::collectSupplierInfo(const std::string& optionsFilePath) {
        std::string id, name, location, branch;

        filesystem::FileReader reader(optionsFilePath, filesystem::DataType::OPTION);

        auto allIds = reader.getAllInitialOptions();
        id = validation::InputValidator::validateSelection("supplier ID", allIds);
        int row = utils::Structures::findVectorIndex(allIds, id);

        auto selectedData = reader.getDataById(id);

        name = validateAndEditOptionsField("supplier name", selectedData[2], optionsFilePath, row, 2);
        location = validateAndEditOptionsField("supplier location", selectedData[3], optionsFilePath, row, 3);
        branch = validateAndEditOptionsField("supplier branch", selectedData[4], optionsFilePath, row, 4);

        return blockchain::SupplierInfo(std::stoi(id), name, location, branch);
    }

    blockchain::TransporterInfo Prompt::collectTransporterInfo(const std::string& optionsFilePath) {
        std::string id, name, productType, transportationType, orderingType;

        filesystem::FileReader reader(optionsFilePath, filesystem::DataType::OPTION);

        // Fetch all transporter IDs for selection
        auto allIds = reader.getAllInitialOptions();
        id = validation::InputValidator::validateSelection("transporter ID", allIds);
        int row = utils::Structures::findVectorIndex(allIds, id);

        auto selectedData = reader.getDataById(id);

        name = validateAndEditOptionsField("supplier name", selectedData[2], optionsFilePath, row, 2);

        auto productTypeOptions = filesystem::FileReader::parseBracketOptions(selectedData[3]);
        productType = collection::validation::InputValidator::validateSelection("transporter product type", productTypeOptions);

        auto transportationTypeOptions = filesystem::FileReader::parseBracketOptions(selectedData[4]);
        transportationType = collection::validation::InputValidator::validateSelection("transporter transportation type", transportationTypeOptions);

        auto orderingTypeOptions = filesystem::FileReader::parseBracketOptions(selectedData[5]);
        orderingType = collection::validation::InputValidator::validateSelection("transporter ordering type", orderingTypeOptions);

        double orderingAmount = validation::InputValidator::validateDouble("transporter ordering payment type (kg)");

        return blockchain::TransporterInfo(std::stoi(id), name, productType, transportationType, orderingType, orderingAmount);
    }

    blockchain::TransactionInfo Prompt::collectTransactionInfo(const std::string& optionsFilePath, const std::string& recordsFilePath) {
        int id, productOrderingLimit;
        std::string retailerPerTripCreditBalance, annualOrderingCreditBalance, paymentType;

        filesystem::FileReader reader(optionsFilePath, filesystem::DataType::OPTION);

        auto allPaymentTypes = reader.getAllInitialOptions();

        std::vector<int> transactionIds = filesystem::FileReader::extractBlockIds(recordsFilePath, "Transaction");

        id = std::stoi(collection::validation::InputValidator::validateUniqueIdInt("transaction ID (unique)", transactionIds));
        retailerPerTripCreditBalance = collection::validation::InputValidator::validateString("retailer per trip credit balance (RM)");
        annualOrderingCreditBalance = collection::validation::InputValidator::validateString("annual ordering credit balance (RM)");
        paymentType = validation::InputValidator::validateSelection("payment type", allPaymentTypes);

        auto selectedData = reader.getDataById(paymentType);

        auto productOrderingLimitOptions = filesystem::FileReader::parseBracketOptions(selectedData[2]);
        std::string productOrderingLimitType = collection::validation::InputValidator::validateSelection("product ordering limit", productOrderingLimitOptions);

        productOrderingLimit = collection::validation::InputValidator::validateInt("product ordering limit (" + productOrderingLimitType + ")");
        std::string productOrderingLimitStr = "(" + productOrderingLimitType + ") " + std::to_string(productOrderingLimit);

        return blockchain::TransactionInfo(id, retailerPerTripCreditBalance, annualOrderingCreditBalance, paymentType, productOrderingLimitStr);
    }

    std::pair<blockchain::enums::BlockAttribute, std::string> Prompt::collectSearchCriteria(const std::vector<std::string>& searchOptions, const std::string& topic) {
        int searchByAttr = collection::validation::InputValidator::validateSelectionInt("an attribute to " + topic + " by", searchOptions);
        std::string searchValue = collection::validation::InputValidator::validateString("a value to " + topic + " for");

        return std::make_pair(static_cast<blockchain::enums::BlockAttribute>(searchByAttr - 1), searchValue);
    }

    void Prompt::collectBlockManipulationCriteria(blockchain::Chain& blockchain, blockchain::Chain& redactedBlockchain, const std::vector<std::string>& searchOptions) {
        using namespace blockchain::enums;

        std::vector<std::string> types = { "Edit", "Delete", "Mine Edited Blocks" };
        int type = validation::InputValidator::validateSelectionInt("Manipulation Type", types);

        if (type == 1) {
            std::vector<std::string> editTypes = { "Soft Edit", "Hard Edit" };

            int editType = validation::InputValidator::validateSelectionInt("Edit Type", editTypes);

            std::vector<std::shared_ptr<blockchain::Block>> foundBlocks;
            do {
                auto [searchAttr, searchValue] = collection::Prompt::collectSearchCriteria(searchOptions, (editType == 1 ? "soft edit" : "hard edit"));
                foundBlocks = (editType == 1 ? redactedBlockchain.searchBlockByAttr(searchAttr, searchValue) : blockchain.searchBlockByAttr(searchAttr, searchValue));

                if (foundBlocks.size() > 1) {
                    std::cout << foundBlocks.size() << " blocks matching the criteria found. Manipulate one block at a time!" << std::endl << std::endl;
                }
            } while (foundBlocks.size() > 1);

            // Found only one block, proceed with editing
            std::shared_ptr<blockchain::BlockInfo> infoPtr;
            switch (foundBlocks[0]->getType()) {
                case blockchain::enums::BlockType::SUPPLIER:
                    infoPtr = std::make_shared<blockchain::SupplierInfo>(
                            collection::Prompt::collectSupplierInfo(data::Config::OPTIONS_SUPPLIER_FILE_PATH));
                    break;

                case blockchain::enums::BlockType::TRANSPORTER:
                    infoPtr = std::make_shared<blockchain::TransporterInfo>(
                            collection::Prompt::collectTransporterInfo(data::Config::OPTIONS_TRANSPORTER_FILE_PATH));
                    break;

                case blockchain::enums::BlockType::TRANSACTION:
                    infoPtr = std::make_shared<blockchain::TransactionInfo>(
                            collection::Prompt::collectTransactionInfo(data::Config::OPTIONS_TRANSACTION_FILE_PATH, data::Config::RECORDS_BLOCKCHAIN_FILE_PATH));
                    break;

                default:
                    std::cerr << "Unsupported block type" << std::endl;
                    return; // Ensure to exit the method if the block type is unsupported
            }

            if (foundBlocks.empty()) {
                std::cout << "No blocks found matching the criteria." << std::endl;
                return;
            }

            redactedBlockchain.editBlock(foundBlocks[0], infoPtr->toString());
            if (editType == 2) {
                blockchain.hardEditBlock(foundBlocks[0], infoPtr->toString());
            }

            std::cout << "Block edited successfully." << std::endl << std::endl;
        } else if (type == 2) {
            std::vector<std::string> delTypes = { "Soft Delete", "Hard Delete" };
            int delType = validation::InputValidator::validateSelectionInt("Delete Type", delTypes);

            std::vector<std::shared_ptr<blockchain::Block>> foundBlocks;
            do {
                auto [searchAttr, searchValue] = collection::Prompt::collectSearchCriteria(searchOptions, (delType == 1 ? "soft delete" : "hard delete"));
                foundBlocks = (delType == 1 ? redactedBlockchain.searchBlockByAttr(searchAttr, searchValue) : blockchain.searchBlockByAttr(searchAttr, searchValue));

                if (foundBlocks.size() > 1) {
                    std::cout << foundBlocks.size() << " blocks matching the criteria found. Manipulate one block at a time!" << std::endl << std::endl;
                }
            } while (foundBlocks.size() > 1);

            if (foundBlocks.empty()) {
                std::cout << "No blocks found matching the criteria." << std::endl;
                return;
            }

            // Found only one block, proceed with deletion
            redactedBlockchain.hideBlock(foundBlocks[0]);
            if (delType == 2) {
                blockchain.hardHideBlock(foundBlocks[0]);
            }

            std::cout << "Block deleted successfully." << std::endl << std::endl;
        } else {
            std::vector<std::shared_ptr<blockchain::Block>> foundBlocks;
            do {
                auto [searchAttr, searchValue] = collection::Prompt::collectSearchCriteria(searchOptions, "mine");
                foundBlocks = blockchain.searchBlockByAttr(searchAttr, searchValue);

                if (foundBlocks.size() > 1) {
                    std::cout << foundBlocks.size() << " blocks matching the criteria found. Manipulate one block at a time!" << std::endl << std::endl;
                }
            } while (foundBlocks.size() > 1);

            if (foundBlocks.empty()) {
                std::cout << "No blocks found matching the criteria." << std::endl;
                return;
            }

            if (foundBlocks[0]->getHeader().isMined()) {
                std::cout << "Block Hash value is already mined to the correct pattern." << std::endl << std::endl;
                return;
            }

            // Found only one block and has validity to be remined, proceed with mining
            redactedBlockchain.mineBlock(foundBlocks[0]);
            blockchain.mineBlock(foundBlocks[0]);

            std::cout << "Block mined successfully." << std::endl << std::endl;
        }
    }
} // namespace collection
