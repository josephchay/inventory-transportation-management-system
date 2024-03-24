#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <set>

namespace collection::validation {
    class InputValidator {
    public:
        static int validateInt(const std::string& topic);
        static double validateDouble(const std::string& topic);
        static std::string validateString(const std::string& topic);
        static std::string validateDateString(const std::string& topic);
        static std::string validateTimeString(const std::string& topic);
        std::string validateCurrencyInput(const std::string& topic);
        static std::string validateSelection(const std::string& topic, const std::vector<std::string>& options);
        static bool validateConfirm(const std::string& topic);
        static bool validateConfirmValue(const std::string& topic, const std::string& value);
        static std::string validateUniqueIdInt(const std::string& topic, const std::vector<int>& existingValues);
        static bool isExitCommand(const std::string& input);
        static bool isEmptyInput(const std::string& input);
    };
}
