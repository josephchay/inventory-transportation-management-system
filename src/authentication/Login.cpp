#include "Login.h"

namespace authentication {
    Login::Login() { }

    bool Login::authenticate(const std::string& username, const std::string& password, const authentication::Participant participant) {
        return participant.getUsername() == username && participant.getPassword() == password;
    }
} // namespace authentication
