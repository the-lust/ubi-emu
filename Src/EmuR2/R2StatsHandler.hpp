#pragma once

namespace Uues::EmuR2 {

class R2StatsHandler {
public:
    static bool GetStats(char* StatNames, int* OutValues, unsigned int Count); // StatNames ignored for now
};

} // namespace Uues::EmuR2