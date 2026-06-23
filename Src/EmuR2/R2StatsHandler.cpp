#include "R2StatsHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

bool R2StatsHandler::GetStats(char* StatNames, int* OutValues, unsigned int Count) {
    auto& logger = Log::Logger::GetInstance();
    logger.Info("[R2Stats] GetStats called with Count=" + std::to_string(Count));

    if (StatNames == nullptr) {
        logger.Warning("[R2Stats] StatNames is null, returning zeros");
    }

    if (OutValues) {
        for (unsigned int i = 0; i < Count; i++) {
            OutValues[i] = 0;
        }
    } else {
        logger.Warning("[R2Stats] OutValues is null, nothing to write");
    }
    return true;
}

} // namespace Uues::EmuR2
