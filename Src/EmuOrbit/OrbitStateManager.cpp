#include "OrbitStateManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuOrbit {
using namespace Uues::Core;

OrbitStateManager& OrbitStateManager::GetInstance() {
    static OrbitStateManager Instance;
    return Instance;
}

void OrbitStateManager::SetAppId(int AppId) {
    if (AppId <= 0) {
        Log::Logger::GetInstance().Warning("[OrbitState] Attempted to set invalid AppId " +
            std::to_string(AppId));
        return;
    }
    mAppId = AppId;
}

int OrbitStateManager::GetAppId() const { return mAppId; }

void OrbitStateManager::SetConfig(const Core::Config::EmulatorConfig& Config) {
    mConfig = Config;
    Log::Logger::GetInstance().Info("[OrbitState] Config applied for user '" + mConfig.UserName + "'");
}

Core::Config::EmulatorConfig& OrbitStateManager::GetConfig() { return mConfig; }

void OrbitStateManager::Reset() {
    mAppId = 0;
    mConfig = Core::Config::EmulatorConfig::LoadDefaults();
    Log::Logger::GetInstance().Info("[OrbitState] State reset to defaults");
}

} // namespace Uues::EmuOrbit
