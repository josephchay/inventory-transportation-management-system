#include "../blockchain/SupplierBlock.h"
#include "InputCollector.h"
#include "validator/InputValidator.h"
#include "../filesystem/FileReader.h"
#include <string>

namespace collection {
    blockchain::SupplierInfo Prompt::collectSupplierInfo(const std::string& optionsFilePath) {
        std::string id, name, location, branch;

        data::FileReader reader(optionsFilePath, data::DataType::OPTION);

        auto allIds = reader.getAllInitialOptions();
        id = validation::InputValidator::validateSelection("supplier ID", allIds);

        auto selectedData = reader.getDataById(id);

        name = selectedData[2];
        name = validation::InputValidator::confirmValue("supplier name", name) ? name : "";

        location = selectedData[3];
        location = validation::InputValidator::confirmValue("supplier location", location) ? location : "";

        branch = selectedData[4];
        branch = validation::InputValidator::confirmValue("supplier branch", branch) ? branch : "";

        return blockchain::SupplierInfo(std::stoi(id), name, location, branch);
    }

    blockchain::TransporterInfo Prompt::collectTransporterInfo(const std::string& optionsFilePath) {
        std::string id, name, productType, transportationType, orderingType;

        data::FileReader reader(optionsFilePath, data::DataType::OPTION);

        // Fetch all transporter IDs for selection
        auto allIds = reader.getAllInitialOptions();
        id = validation::InputValidator::validateSelection("transporter ID", allIds);

        auto selectedData = reader.getDataById(id);

        name = selectedData[2];
        name = validation::InputValidator::confirmValue("transporter name", name) ? name : "";

        auto productTypeOptions = data::FileReader::parseBracketOptions(selectedData[3]);
        productType = collection::validation::InputValidator::validateSelection("transporter product type", productTypeOptions);

        auto transportationTypeOptions = data::FileReader::parseBracketOptions(selectedData[4]);
        transportationType = collection::validation::InputValidator::validateSelection("transporter transportation type", transportationTypeOptions);

        auto orderingTypeOptions = data::FileReader::parseBracketOptions(selectedData[5]);
        orderingType = collection::validation::InputValidator::validateSelection("transporter ordering type", orderingTypeOptions);

        double orderingAmount = validation::InputValidator::validateDouble("transporter ordering payment type (kg)");

        return blockchain::TransporterInfo(std::stoi(id), name, productType, transportationType, orderingType, orderingAmount);
    }

    blockchain::TransactionInfo Prompt::collectTransactionInfo(const std::string& optionsFilePath) {
        int id;
        std::string retailerPerTripCreditBalance, annualOrderingCreditBalance, paymentType, productOrderingLimit;

        data::FileReader reader(optionsFilePath, data::DataType::OPTION);

        auto allPaymentTypes = reader.getAllInitialOptions();

        id = collection::validation::InputValidator::validateInt("transaction ID (unique)");
        retailerPerTripCreditBalance = collection::validation::InputValidator::validateString("retailer per trip credit balance (RM)");
        annualOrderingCreditBalance = collection::validation::InputValidator::validateString("annual ordering credit balance (RM)");
        paymentType = validation::InputValidator::validateSelection("supplier ID", allPaymentTypes);

        auto selectedData = reader.getDataById(paymentType);

        auto productOrderingLimitOptions = data::FileReader::parseBracketOptions(selectedData[2]);
        productOrderingLimit = collection::validation::InputValidator::validateSelection("product ordering limit", productOrderingLimitOptions);

        return blockchain::TransactionInfo(id, retailerPerTripCreditBalance, annualOrderingCreditBalance, paymentType, productOrderingLimit);
    }
} // namespace collection
