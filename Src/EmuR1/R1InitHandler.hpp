#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1InitHandler {
public:
    static bool HandleInit(unsigned int Version, int AppId);
    static bool HandleShutdown();
    static bool IsInitialized();

private:
    static bool mInitialized; // not thread-safe, but good enough for now
};

} // namespace Uues::EmuR1