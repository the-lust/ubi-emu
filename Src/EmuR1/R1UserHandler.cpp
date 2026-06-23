#include "R1UserHandler.hpp"
#include "R1StateManager.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

Common::String R1UserHandler::GetUsername() {
    return R1StateManager::GetInstance().GetConfig().UserName;
}

Common::String R1UserHandler::GetUsernameUtf8() {
    return GetUsername();
}

Common::String R1UserHandler::GetEmail() {
    return R1StateManager::GetInstance().GetConfig().Email;
}

// we don't store passwords - return empty
// some games call this and crash if it's null, so return empty string
Common::String R1UserHandler::GetPassword() {
    return "";
}
Common::String R1UserHandler::GetPasswordUtf8() {
    return "";
}

Common::String R1UserHandler::GetCredentials() {
    // format is "email:" (password is always empty)
    auto email = GetEmail();
    if (email.empty()) {
        return ":";
    }
    return email + ":";
}

} // namespace Uues::EmuR1
