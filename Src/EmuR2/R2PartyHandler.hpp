#pragma once

namespace Uues::EmuR2 {

class R2PartyHandler {
public:
    static bool GetGameSession(unsigned int* OutSessionId);
    static bool SetGameSession(unsigned int SessionId); // returns true always
};

} // namespace Uues::EmuR2