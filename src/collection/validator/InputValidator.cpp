#include "InputValidator.h"
#include <iostream>
#include <set>

namespace collection::validation {
    /**
     * @brief Get a string input from the currentParticipant and provides error handling for empty inputs.
     *
     * @param topic
     * @return
     */
    std::string InputValidator::validateString(const std::string& topic) {
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);

            if (isExitCommand(input) || !isEmptyInput(input)) {
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

            if (isExitCommand(input) || isEmptyInput(input)) continue;

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
     * @brief Validates currentParticipant input to ensure it is a valid double value.
     *
     * This function prompts the currentParticipant with a custom message and attempts to read
     * a double value from the input. If the input is not a valid double, the function
     * clears the error state of cin, discards the invalid input, and prompts the currentParticipant again.
     * This process repeats until a valid double is entered.
     *
     * @param topic The custom message displayed to the currentParticipant prompting for input.
     * @return A valid double value entered by the currentParticipant.
     */
    double InputValidator::validateDouble(const std::string& topic) {
        double value;
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);

            if (isExitCommand(input) || isEmptyInput(input)) continue;

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
     * This function prompts the currentParticipant with a custom message and reads an input string.
     * It then checks if the input matches the expected date format (dd/mm/yyyy) using
     * a regular expression. If the input does not match, it prompts the currentParticipant again.
     * This process repeats until a valid date format is entered.
     *
     * @param topic The custom message displayed to the currentParticipant prompting for input.
     * @return A valid date string in the format dd/mm/yyyy.
     */
    std::string InputValidator::validateDateString(const std::string& topic) {
        std::regex datePattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/\d{4}$)");
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);

            if (isExitCommand(input) || isEmptyInput(input)) continue;

            if (!std::regex_match(input, datePattern)) {
                std::cout << "Invalid date format. Please enter in dd/mm/yyyy format.\n";
            } else {
                return input;
            }
        }
    }

    /**
     * @brief Validates a time string against a 12-hour clock format with AM/PM.
     *
     * This function prompts the currentParticipant with a custom message and reads an input string.
     * It checks if the input matches the expected time format (hh:mm AM/PM, with flexible
     * spacing and case sensitivity) using a regular expression. If the input does not match,
     * it prompts the currentParticipant again. This process repeats until a valid time format is entered.
     *
     * @param topic The custom message displayed to the currentParticipant prompting for input.
     * @return A valid time string in the format hh:mm AM/PM.
     */
    std::string InputValidator::validateTimeString(const std::string& topic) {
        validateString(topic);
        std::regex timePattern(R"(^(1[0-2]|0?[1-9]):([0-5]?[0-9]) ?([AaPp][Mm])$)");
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);

            if (isExitCommand(input) || isEmptyInput(input)) continue;

            if (!std::regex_match(input, timePattern)) {
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
     * This function prompts the currentParticipant for a productOrderingLimit value, ensuring that the input
     * matches a numeric format with at most two decimal places. It does not accept
     * productOrderingLimit symbols or any non-numeric characters except for the decimal point,
     * and ensures that if a decimal point is present, it is followed by no more than
     * two digits.
     *
     * @param topic The message displayed to the currentParticipant prompting for input.
     * @return A string representing a valid numeric productOrderingLimit value.
     */
    std::string InputValidator::validateCurrencyInput(const std::string& topic) {
        std::regex currencyPattern(R"(^[0-9]+(\.[0-9]{1,2})?$)");
        std::string input;
        do {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);

            if (isExitCommand(input) || isEmptyInput(input)) continue;

            if (!std::regex_match(input, currencyPattern)) {
                std::cout << "Invalid currency format. Please enter a numeric value with at most two decimal places (e.g., 1234.56).\n";
            } else {
                break; // Valid currency format
            }
        } while (true);

        return input;
    }

    std::string InputValidator::validateSelection(const std::string& topic, const std::vector<std::string>& options) {
        std::string input;
        while (true) {
            // Display options
            for (size_t i = 0; i < options.size(); ++i) {
                std::cout << (i + 1) << ". " << options[i] << std::endl;
            }

            // Get currentParticipant's choice
            std::cout << "Select " << topic << ": ";
            std::getline(std::cin, input); // Use getline to read the input as a string

            if (isExitCommand(input)) break;

            try {
                int choice = std::stoi(input); // Convert input to integer

                if (choice < 1 || choice > static_cast<int>(options.size())) {
                    std::cout << "Invalid selection. Please try again.\n";
                    continue; // Invalid selection, show options again
                }

                std::cout << "Selected " << topic << ": " << options[choice - 1] << std::endl << std::endl;
                return options[choice - 1]; // Return the selected option
            } catch (std::invalid_argument& e) {
                // Non-integer input that's not an exit command
                std::cout << "Invalid input. Please enter a number or 'q' to quit.\n";
            } catch (std::out_of_range& e) {
                // Input number too large for int
                std::cout << "Selection out of range. Please try again.\n";
            }
        }

        return ""; // Return an empty string or handle this case as needed
    }

    int InputValidator::validateSelectionInt(const std::string& topic, const std::vector<std::string>& options) {
        // Use validateSelection to get the selected option
        std::string selectedOption = validateSelection(topic, options);

        // Check if the currentParticipant has decided to exit
        if (selectedOption.empty() || isExitCommand(selectedOption)) {
            return -1; // or any other indicator that currentParticipant exited or invalid selection was made
        }

        // Find the index of the selected option
        auto it = std::find(options.begin(), options.end(), selectedOption);
        if (it != options.end()) {
            return std::distance(options.begin(), it) + 1; // Add 1 to convert from 0-based to 1-based index
        }

        // In case something goes wrong and the selected option is not found (which shouldn't happen)
        return -1;
    }

    bool InputValidator::validateConfirmValue(const std::string& topic, const std::string& value) {
        std::string input;
        // Loop until a valid response is received
        while (true) {
            std::cout << "Confirm " << topic << ": " << value << "\nConfirm? (y/n): ";
            std::getline(std::cin, input);

            if (isExitCommand(input)) break;

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

        return false;
    }

    /**
     * @brief Validates currentParticipant input to ensure it is unique compared to a set of existing values.
     *
     * This function prompts the currentParticipant with a custom message and attempts to read a string value from the input.
     * It then checks if the input is already present in a provided set of existing values. If the input is not unique,
     * it prompts the currentParticipant again. This process repeats until a unique input is entered.
     *
     * @param topic The custom message displayed to the currentParticipant prompting for input.
     * @param existingValues The set of existing values to compare against for uniqueness.
     * @return A unique string value entered by the currentParticipant.
     */
    std::string InputValidator::validateUniqueIdInt(const std::string& topic, const std::vector<int>& existingValues) {
        int value;
        std::string input;
        while (true) {
            std::cout << "Enter " << topic << ": ";
            std::getline(std::cin, input);

            if (isExitCommand(input)) continue;
            if (isEmptyInput(input)) continue;

            std::stringstream inputStream(input);
            if (!(inputStream >> value) || !(inputStream.eof())) {
                std::cout << "Invalid input. Please enter an integer.\n";
                continue;
            }

            if (std::find(existingValues.begin(), existingValues.end(), value) != existingValues.end()) {
                std::cout << "The entered " << topic << " has been taken. Please enter a unique value.\n";
            } else {
                std::cout << "Entered " << topic << ": " << value << std::endl << std::endl;
                return std::to_string(value); // Convert the integer back to string for return
            }
        }
    }

    /**
     * @brief Check if the input is an exit command.
     * If the input is 'q' or 'quit', the program will exit.
     *
     * @param input
     * @return
     */
    bool InputValidator::isExitCommand(const std::string& input) {
        if (input == "q" || input == "quit") {
            std::exit(0); // Use exit(0) to terminate the program
        }
        return false;
    }

    /**
     * @brief Check if the input is an empty input.
     * If the input is empty, the currentParticipant will be prompted to enter a non-empty input.
     *
     * @param input
     * @return
     */
    bool InputValidator::isEmptyInput(const std::string& input) {
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please try again.\n";
            return true;
        }
        return false;
    }
}
