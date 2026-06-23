#include "R1RichPresenceHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

static Common::String s_CurrentPresence = "InMenu";

bool R1RichPresenceHandler::SetPresence(const Common::String& Presence) {
    s_CurrentPresence = Presence;
    Log::Logger::GetInstance().Debug("[R1Presence] Set to: " + Presence);
    return true;
}

Common::String R1RichPresenceHandler::GetPresence() {
    return s_CurrentPresence;
}

} // namespace Uues::EmuR1
