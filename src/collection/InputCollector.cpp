#include "../blockchain/SupplierBlock.h"
#include "InputCollector.h"
#include "validator/InputValidator.h"
#include "../filesystem/FileReader.h"
#include "../filesystem/FileWriter.h"
#include "../utils/Structures.h"
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
        int id;
        std::string retailerPerTripCreditBalance, annualOrderingCreditBalance, paymentType, productOrderingLimit;

        filesystem::FileReader reader(optionsFilePath, filesystem::DataType::OPTION);

        auto allPaymentTypes = reader.getAllInitialOptions();

        std::vector<int> transactionIds = filesystem::FileReader::extractBlockIds(recordsFilePath, "Transaction");

        id = std::stoi(collection::validation::InputValidator::validateUniqueIdInt("transaction ID (unique)", transactionIds));
        retailerPerTripCreditBalance = collection::validation::InputValidator::validateString("retailer per trip credit balance (RM)");
        annualOrderingCreditBalance = collection::validation::InputValidator::validateString("annual ordering credit balance (RM)");
        paymentType = validation::InputValidator::validateSelection("supplier ID", allPaymentTypes);

        auto selectedData = reader.getDataById(paymentType);

        auto productOrderingLimitOptions = filesystem::FileReader::parseBracketOptions(selectedData[2]);
        std::string productOrderingLimitType = collection::validation::InputValidator::validateSelection("product ordering limit", productOrderingLimitOptions);

        productOrderingLimit = collection::validation::InputValidator::validateString("product ordering limit (" + productOrderingLimitType + ")");
        productOrderingLimit = "(" + productOrderingLimitType + ") " + productOrderingLimit;

        return blockchain::TransactionInfo(id, retailerPerTripCreditBalance, annualOrderingCreditBalance, paymentType, productOrderingLimit);
    }

    std::pair<blockchain::enums::BlockAttribute, std::string> Prompt::collectSearchCriteria(const std::vector<std::string>& searchOptions, const std::string& topic) {
        int searchByAttr = collection::validation::InputValidator::validateSelectionInt("an attribute to " + topic + " by", searchOptions);
        std::string searchValue = collection::validation::InputValidator::validateString("a value to " + topic + " for");

        return std::make_pair(static_cast<blockchain::enums::BlockAttribute>(searchByAttr - 1), searchValue);
    }

    void Prompt::collectBlockManipulationCriteria(blockchain::Chain& blockchain, blockchain::Chain& redactedBlockchain, const std::vector<std::string>& searchOptions) {
        std::vector<std::string> types = { "Edit", "Delete" };
        int type = validation::InputValidator::validateSelectionInt("Manipulation Type", types);

        if (type == 1) {

        } else {
            std::vector<std::string> delTypes = { "Soft Delete", "Hard Delete" };
            int delType = validation::InputValidator::validateSelectionInt("Delete Type", delTypes);

            std::vector<std::shared_ptr<blockchain::Block>> foundBlocks;
            do {
                auto [searchAttr, searchValue] = collection::Prompt::collectSearchCriteria(searchOptions, (delType == 1 ? "soft delete" : "hard delete"));
                foundBlocks = blockchain.searchBlockByAttr(searchAttr, searchValue);

                if (foundBlocks.size() > 1) {
                    std::cout << foundBlocks.size() << " blocks matching the criteria found. Manipulate one block at a time!" << std::endl << std::endl;
                }
            } while (foundBlocks.size() > 1);

            redactedBlockchain.hideBlock(foundBlocks[0]);
            if (delType == 2) {
                blockchain.removeBlock(foundBlocks[0]);
            }
        }
    }
} // namespace collection
