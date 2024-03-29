#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <set>

namespace collection::validation {
    class InputValidator {
    public:
        /**
         * @brief Validate an integer input.
         * Checks if the input is a valid integer.
         *
         * @param topic
         * @return
         */
        static int validateInt(const std::string& topic);

        /**
         * @brief Validate a double input.
         * Checks if the input is a valid double.
         *
         * @param topic
         * @return
         */
        static double validateDouble(const std::string& topic);

        /**
         * @brief Validate a string input.
         * Checks if the input is a valid string.
         *
         * @param topic
         * @return
         */
        static std::string validateString(const std::string& topic);

        /**
         * @brief Validate a date string input.
         * Checks if the input is a valid date string.
         *
         * @param topic
         * @return
         */
        static std::string validateDateString(const std::string& topic);

        /**
         * @brief Validate a time string input.
         * Checks if the input is a valid time string.
         *
         * @param topic
         * @return
         */
        static std::string validateTimeString(const std::string& topic);

        /**
         * @brief Validate a currency input.
         *
         * @param topic
         * @return
         */
        std::string validateCurrencyInput(const std::string& topic);

        /**
         * @brief Validate a selection input.
         *
         * @param topic
         * @param options
         * @return
         */
        static std::string validateSelection(const std::string& topic, const std::vector<std::string>& options);

        /**
         * @brief Validate a selection input.
         *
         * @param topic
         * @param options
         * @return
         */
        static int validateSelectionInt(const std::string& topic, const std::vector<std::string>& options);

        /**
         * @brief Validate a confirm value input.
         *
         * @param topic
         * @param value
         * @return
         */
        static bool validateConfirmValue(const std::string& topic, const std::string& value = "");

        /**
         * @brief Validate a unique id input.
         *
         * @param topic
         * @param existingValues
         * @return
         */
        static std::string validateUniqueIdInt(const std::string& topic, const std::vector<int>& existingValues);

        /**
         * @brief Validate if the input is an exit command.
         *
         * @param input
         * @return
         */
        static bool isExitCommand(const std::string& input);

        /**
         * @brief Validate if the input is an empty input.
         *
         * @param input
         * @return
         */
        static bool isEmptyInput(const std::string& input);
    };
}
