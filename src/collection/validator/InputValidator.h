#pragma once

#include <iostream>
#include <string>
#include <regex>

namespace collection::validation {
    class InputValidator {
    public:
        static int validateInt(const std::string& prompt);
        static double validateDouble(const std::string& prompt);
        static std::string validateString(const std::string& prompt);
        static std::string validateDateString(const std::string& prompt);
        static std::string validateTimeString(const std::string& prompt);
        std::string validateCurrencyInput(const std::string& prompt);
        static std::string validateSelection(const std::string& prompt, const std::vector<std::string>& options);
        static bool confirmValue(const std::string& prompt, const std::string& value);
    };
}
