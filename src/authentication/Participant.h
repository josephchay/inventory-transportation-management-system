#ifndef PARTICIPANT_PARTICIPANT_H
#define PARTICIPANT_PARTICIPANT_H

#include <string>

namespace authentication {
    class Participant {
    private:
        int id; /* Unique identifier for the participant */
        std::string username; /* Username for the participant */
        std::string password; /* Password for the participant */
        std::string fullName; /* First Name plus Last Name of the participant */
        std::string industryRole; /* Industry of the participant: Supplier, Transporter, Accountancy, or Administration */
        std::string role;

    public:
        /**
         * @brief Construct a new Participant object
         *
         * @param id
         * @param username
         * @param password
         * @param fullName
         * @param industryRole
         * @param role
         */
        Participant(int id, const std::string& username, const std::string& password, const std::string& fullName, const std::string& industryRole, const std::string& role);

        // Getters
        [[nodiscard]] int getId() const;
        [[nodiscard]] std::string getUsername() const;
        [[nodiscard]] std::string getPassword() const;
        [[nodiscard]] std::string getFullName() const;
        [[nodiscard]] std::string getIndustryRole() const;
        [[nodiscard]] std::string getRole() const;
        [[nodiscard]] double getBalance() const;
        [[nodiscard]] double getTotalSpent() const;
    };
}

#endif // PARTICIPANT_PARTICIPANT_H
