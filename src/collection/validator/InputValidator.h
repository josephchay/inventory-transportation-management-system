#pragma once

#include <iostream>
#include <string>
#include <regex>

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
        static bool confirmValue(const std::string& topic, const std::string& value);
    };
}
