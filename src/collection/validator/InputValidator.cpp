#include "InputValidator.h"
#include <iostream>
#include <limits>

namespace collection::validation {
    /**
     * @brief Get a string input from the user and provides error handling for empty inputs.
     *
     * @param topic
     * @return
     */
    std::string InputValidator::validateString(const std::string& topic) {
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Input cannot be empty. Please try again.\n";
            } else {
                std::cout << "Entered " << topic << ": " << input << std::endl << std::endl;
                return input; // Return the valid, non-empty input
            }
        }
    }

    /**
     * @brief Check if the input is an integer and provides error handling for invalid inputs other than integer values.
     *
     * @param topic
     * @return
     */
    int InputValidator::validateInt(const std::string& topic) {
        int value;
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Input cannot be empty. Please try again.\n";
                continue;
            }
            std::stringstream inputStream(input);
            if (!(inputStream >> value) || !(inputStream.eof())) { // Checks for exact match and no extra characters
                std::cout << "Invalid input. Please enter an integer.\n";
            } else {
                std::cout << "Entered " << topic << ": " << value << std::endl << std::endl;
                return value;
            }
        }
    }

    /**
     * @brief Validates user input to ensure it is a valid double value.
     *
     * This function prompts the user with a custom message and attempts to read
     * a double value from the input. If the input is not a valid double, the function
     * clears the error state of cin, discards the invalid input, and prompts the user again.
     * This process repeats until a valid double is entered.
     *
     * @param topic The custom message displayed to the user prompting for input.
     * @return A valid double value entered by the user.
     */
    double InputValidator::validateDouble(const std::string& topic) {
        double value;
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Input cannot be empty. Please try again.\n";
                continue;
            }
            std::stringstream inputStream(input);
            if (!(inputStream >> value) || !(inputStream.eof())) { // Checks for exact match and no extra characters
                std::cout << "Invalid input. Please enter a valid number.\n";
            } else {
                std::cout << "Entered " << topic << ": " << value << std::endl << std::endl;
                return value;
            }
        }
    }

    /**
     * @brief Validates a date string against the format dd/mm/yyyy.
     *
     * This function prompts the user with a custom message and reads an input string.
     * It then checks if the input matches the expected date format (dd/mm/yyyy) using
     * a regular expression. If the input does not match, it prompts the user again.
     * This process repeats until a valid date format is entered.
     *
     * @param topic The custom message displayed to the user prompting for input.
     * @return A valid date string in the format dd/mm/yyyy.
     */
    std::string InputValidator::validateDateString(const std::string& topic) {
        std::regex datePattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/\d{4}$)");
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Input cannot be empty. Please try again.\n";
            } else if (!std::regex_match(input, datePattern)) {
                std::cout << "Invalid date format. Please enter in dd/mm/yyyy format.\n";
            } else {
                return input;
            }
        }
    }

    /**
     * @brief Validates a time string against a 12-hour clock format with AM/PM.
     *
     * This function prompts the user with a custom message and reads an input string.
     * It checks if the input matches the expected time format (hh:mm AM/PM, with flexible
     * spacing and case sensitivity) using a regular expression. If the input does not match,
     * it prompts the user again. This process repeats until a valid time format is entered.
     *
     * @param topic The custom message displayed to the user prompting for input.
     * @return A valid time string in the format hh:mm AM/PM.
     */
    std::string InputValidator::validateTimeString(const std::string& topic) {
        validateString(topic);
        std::regex timePattern(R"(^(1[0-2]|0?[1-9]):([0-5]?[0-9]) ?([AaPp][Mm])$)");
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Input cannot be empty. Please try again.\n";
            } else if (!std::regex_match(input, timePattern)) {
                std::cout << "Invalid time format. Please enter in hh:mm AM/PM format.\n";
            } else {
                return input;
            }
        }
    }

    /**
     * @brief Validates a numeric productOrderingLimit string to ensure it is properly formatted
     * with at most two decimal places.
     *
     * This function prompts the user for a productOrderingLimit value, ensuring that the input
     * matches a numeric format with at most two decimal places. It does not accept
     * productOrderingLimit symbols or any non-numeric characters except for the decimal point,
     * and ensures that if a decimal point is present, it is followed by no more than
     * two digits.
     *
     * @param topic The message displayed to the user prompting for input.
     * @return A string representing a valid numeric productOrderingLimit value.
     */
    std::string InputValidator::validateCurrencyInput(const std::string& topic) {
        std::regex currencyPattern(R"(^[0-9]+(\.[0-9]{1,2})?$)");
        std::string input;
        do {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "Input cannot be empty. Please try again.\n";
            } else if (!std::regex_match(input, currencyPattern)) {
                std::cout << "Invalid currency format. Please enter a numeric value with at most two decimal places (e.g., 1234.56).\n";
            } else {
                break; // Valid currency format
            }
        } while (true);

        return input;
    }

    std::string InputValidator::validateSelection(const std::string& topic, const std::vector<std::string>& options) {
        std::string selectedOption;
        while (true) {
            // Display options
            for (size_t i = 0; i < options.size(); ++i) {
                std::cout << (i + 1) << ". " << options[i] << std::endl;
            }

            // Get user's choice
            std::cout << "Select " << topic << ": ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

            if (std::cin.fail() || choice < 1 || choice > static_cast<int>(options.size())) {
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input
                std::cout << "Invalid selection. Please try again.\n";
                continue; // Go back to showing options
            }

            selectedOption = options[choice - 1];
            std::cout << "Selected " << topic << ": " << selectedOption << std::endl << std::endl;
            break; // Valid selection, exit loop
        }

        return selectedOption;
    }

    bool InputValidator::confirmValue(const std::string& topic, const std::string& value) {
        std::string input;
        // Loop until a valid response is received
        while (true) {
            std::cout << "Confirm " << topic << ": " << value << "\nConfirm? (y/n): ";
            std::cin >> input;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character

            // Check for valid input
            if (input == "y" || input == "Y") {
                std::cout << "Confirmed " << topic << ": " << value << std::endl << std::endl;
                return true;
            } else if (input == "n" || input == "N") {
                return false;
            } else {
                std::cout << "Invalid input. Please enter 'y' or 'Y' or 'n' or 'N' only.\n";
            }
        }
    }
}
