#include "Participant.h"

namespace authentication {
    Participant::Participant(int id, const std::string& username, const std::string& password, const std::string& fullName, const std::string& industryRole, const std::string& role)
            : id(id), username(username), password(password), fullName(fullName), industryRole(industryRole), role(role) {}

    int Participant::getId() const { return id; }
    std::string Participant::getUsername() const { return username; }
    std::string Participant::getPassword() const { return password; }
    std::string Participant::getFullName() const { return fullName; }
    std::string Participant::getIndustryRole() const { return industryRole; }
    std::string Participant::getRole() const { return role; }
}
