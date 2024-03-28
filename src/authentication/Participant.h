#ifndef PARTICIPANT_PARTICIPANT_H
#define PARTICIPANT_PARTICIPANT_H

#include <string>

namespace authentication {
    class Participant {
    private:
        int id;
        std::string username;
        std::string password;
        std::string fullName;
        std::string department;
        std::string role;

    public:
        Participant(int id, const std::string& username, const std::string& password, const std::string& fullName, const std::string& department, const std::string& role);

        // Accessors
        int getId() const;
        std::string getUsername() const;
        std::string getPassword() const;
        std::string getFullName() const;
        std::string getIndustryRole() const;
        std::string getRole() const;
    };
}

#endif // PARTICIPANT_PARTICIPANT_H
