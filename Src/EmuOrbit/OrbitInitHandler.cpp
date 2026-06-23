#include "OrbitInitHandler.hpp"
#include "OrbitStateManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuOrbit {
using namespace Uues::Core;

bool OrbitInitHandler::mInitialized = false;
int OrbitInitHandler::mAppId = 0;
unsigned int OrbitInitHandler::mSdkVersion = 0;

bool OrbitInitHandler::HandleInit(unsigned int Version, int AppId) {
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[OrbitInit] Re-init with AppId=" +
            std::to_string(AppId) + " (was " + std::to_string(mAppId) + ")");
        // allow re-init with different AppId
        if (mAppId == AppId) return true;
    }
    if (AppId <= 0) {
        Log::Logger::GetInstance().Error("[OrbitInit] Invalid AppId: " + std::to_string(AppId));
        return false;
    }

    mAppId = AppId;
    mSdkVersion = Version;
    OrbitStateManager::GetInstance().SetAppId(AppId);
    mInitialized = true;

    Log::Logger::GetInstance().Info("[OrbitInit] Initialized (SDK v" +
        std::to_string(Version) + ", AppId=" + std::to_string(AppId) + ")");
    return true;
}

bool OrbitInitHandler::HandleShutdown() {
    if (!mInitialized) {
        Log::Logger::GetInstance().Warning("[OrbitInit] Shutdown called but not initialized");
        return false;
    }
    Log::Logger::GetInstance().Info("[OrbitInit] Shutdown");
    mInitialized = false;
    mAppId = 0;
    mSdkVersion = 0;
    return true;
}

bool OrbitInitHandler::IsInitialized() { return mInitialized; }

} // namespace Uues::EmuOrbit
