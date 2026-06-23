#include "UpcAuthHandler.hpp"
#include "../Core/Storage/UserProfile.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

// cache this so we don't keep hitting the profile store
static Common::String sLastUsername;
static bool        sAuthed = false;

Common::String UpcAuthHandler::GetUsername() {
    auto name = Storage::UserProfile::GetInstance().GetUserName();
    sLastUsername = name;
    return name;
}

Common::String UpcAuthHandler::GetEmail() {
    return Storage::UserProfile::GetInstance().GetEmail();
}

bool UpcAuthHandler::Authenticate([[maybe_unused]] const Common::String& token) {
    // FIXME: actually validate the token against the server
    // for now we just assume it's valid
    sAuthed      = true;
    Log::Logger::GetInstance().Info("[UPCAuth] Authenticated (offline mode)");
    return true;
}

} // namespace Uues::EmuUPC
