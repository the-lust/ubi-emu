#pragma once

namespace Uues::EmuR1 {

class R1PartyHandler {
public:
    static bool Init();
    static bool Shutdown();

private:
    R1PartyHandler() = delete; // static helper
};

} // namespace Uues::EmuR1