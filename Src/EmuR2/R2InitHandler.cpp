#include "R2InitHandler.hpp"
#include "R2StateManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

bool R2InitHandler::mInitialized = false;
int R2InitHandler::mAppId = 0;

bool R2InitHandler::HandleInit(unsigned int Version, int AppId) {
    if (mInitialized) {
        // already initialized, skip
        return true;
    }
    // TODO: should we validate Version?
    mAppId = AppId;
    R2StateManager::GetInstance().SetAppId(AppId);
    mInitialized = true;
    Log::Logger::GetInstance().Info("[R2Init] Initialized AppId=" + std::to_string(AppId));
    return true;
}

bool R2InitHandler::HandleShutdown() {
    mInitialized = false;
    return true;
}

bool R2InitHandler::IsInitialized() {
    bool retVal = mInitialized;
    return retVal;
}

} // namespace Uues::EmuR2
