#ifndef LOGIN_LOGIN_H
#define LOGIN_LOGIN_H

#include <map>
#include <string>
#include <vector>
#include "Participant.h"

namespace authentication {
    class Login {
    private:
        std::map<std::string, std::string> credentials; // Store username and password pairs

    public:
        Login();

        // Method to authenticate a user
        bool authenticate(const std::string& username, const std::string& password, const authentication::Participant participant);
    };
} // namespace authentication

#endif // LOGIN_LOGIN_H
