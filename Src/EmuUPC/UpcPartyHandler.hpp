#pragma once

namespace Uues::EmuUPC {

class UpcPartyHandler {
public:
    static bool GetSessionId(unsigned int* OutSessionId);
    static bool SetSessionId(unsigned int SessionId);
};

} // namespace Uues::EmuUPC