#include "R2UserHandler.hpp"
#include "../Core/Storage/UserProfile.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

Common::String R2UserHandler::GetUsername() {
    auto& Profile = Storage::UserProfile::GetInstance();
    Common::String name = Profile.GetUserName();
    if (name.empty()) name = "Player";
    return name;
}

Common::String R2UserHandler::GetEmail() {
    auto& Profile = Storage::UserProfile::GetInstance();
    Common::String email = Profile.GetEmail();
    return email;
}

} // namespace Uues::EmuR2
