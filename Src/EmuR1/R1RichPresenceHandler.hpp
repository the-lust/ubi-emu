#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1RichPresenceHandler {
public:
    static bool SetPresence(const Core::Common::String& Presence);
    static Core::Common::String GetPresence();

private:
    R1RichPresenceHandler() = delete; // not instantiable
};

} // namespace Uues::EmuR1