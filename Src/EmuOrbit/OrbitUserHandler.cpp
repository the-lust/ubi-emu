#include "OrbitUserHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Storage/UserProfile.hpp"

namespace Uues::EmuOrbit {
using namespace Uues::Core;

Common::String OrbitUserHandler::GetName() {
    auto Name = Core::Storage::UserProfile::GetInstance().GetUserName();
    if (Name.empty()) {
        Log::Logger::GetInstance().Warning("[OrbitUser] No user name set, falling back to 'Player'");
        Name = "Player";
    }
    return Name;
}

Common::String OrbitUserHandler::GetId() {
    auto Id = Core::Storage::UserProfile::GetInstance().GetUserId();
    if (Id.empty()) {
        Log::Logger::GetInstance().Warning("[OrbitUser] No user id set, generating fake one");
        Id = "orbit-user-" + std::to_string(static_cast<int>(reinterpret_cast<intptr_t>(&Id)));
    }
    return Id;
}

} // namespace Uues::EmuOrbit
