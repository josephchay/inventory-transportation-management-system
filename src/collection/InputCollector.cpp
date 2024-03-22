#include "../blockchain/SupplierBlock.h"
#include "InputCollector.h"
#include "validator/InputValidator.h"
#include "../filesystem/FileReader.h"
#include <string>

namespace collection {
    blockchain::SupplierInfo Prompt::collectSupplierInfo(const std::string& optionsFilePath) {
        data::FileReader reader(optionsFilePath);

        auto allIds = reader.getAllIds();
        std::string selectedId = validation::InputValidator::validateSelection("Select supplier ID: ", allIds);

        auto selectedData = reader.getDataById(selectedId);

        std::string supplierName = selectedData[2];
        supplierName = validation::InputValidator::confirmValue("Confirm supplier name: ", supplierName) ? supplierName : "";

        std::string supplierLocation = selectedData[3];
        supplierLocation = validation::InputValidator::confirmValue("Confirm supplier location: ", supplierLocation) ? supplierLocation : "";

        std::string supplierBranch = selectedData[4];
        supplierBranch = validation::InputValidator::confirmValue("Confirm supplier branch: ", supplierBranch) ? supplierBranch : "";

        return blockchain::SupplierInfo(std::stoi(selectedId), supplierName, supplierLocation, supplierBranch);
    }

    blockchain::TransporterInfo Prompt::collectTransporterInfo(const std::string& optionsFilePath) {
        data::FileReader reader(optionsFilePath);

        // Fetch all transporter IDs for selection
        auto allIds = reader.getAllIds();
        std::string selectedId = validation::InputValidator::validateSelection("Select transporter ID: ", allIds);

        auto selectedData = reader.getDataById(selectedId);

        std::string transporterName = selectedData[2];
        transporterName = validation::InputValidator::confirmValue("Confirm transporter name: ", transporterName) ? transporterName : "";

        auto productTypeOptions = data::FileReader::parseBracketOptions(selectedData[3]);
        std::string productType = collection::validation::InputValidator::validateSelection("Select transporter product type: ", productTypeOptions);

        auto transportationTypeOptions = data::FileReader::parseBracketOptions(selectedData[4]);
        std::string transportationType = collection::validation::InputValidator::validateSelection("Select transporter transportation type: ", transportationTypeOptions);

        auto orderingTypeOptions = data::FileReader::parseBracketOptions(selectedData[5]);
        std::string orderingType = collection::validation::InputValidator::validateSelection("Select transporter ordering type: ", orderingTypeOptions);

        double orderingAmount = validation::InputValidator::validateDouble("Enter transporter ordering payment type (kg): ");

        return blockchain::TransporterInfo(std::stoi(selectedId), transporterName, productType, transportationType, orderingType, orderingAmount);
    }

    blockchain::TransactionInfo Prompt::collectTransactionInfo(const std::string& optionsFilePath) {
        int transactionID, paymentType, productOrderingLimit;
        std::string retailerPerTripCreditBalance, annualOrderingCreditBalance;

        transactionID = collection::validation::InputValidator::validateInt("Enter transaction ID: ");
        retailerPerTripCreditBalance = collection::validation::InputValidator::validateString("Enter retailer per trip credit balance: ");
        annualOrderingCreditBalance = collection::validation::InputValidator::validateString("Enter annual ordering credit balance: ");
        paymentType = collection::validation::InputValidator::validateInt("Enter payment type: ");
        productOrderingLimit = collection::validation::InputValidator::validateInt("Enter product ordering limit: ");

        data::FileReader reader(optionsFilePath);

        auto allIds = reader.getAllIds();
        std::string selectedId = validation::InputValidator::validateSelection("Select transaction ID: ", allIds);

        auto selectedData = reader.getDataById(selectedId);

        return blockchain::TransactionInfo(transactionID, retailerPerTripCreditBalance, annualOrderingCreditBalance, paymentType, productOrderingLimit);
    }
} // namespace collection
