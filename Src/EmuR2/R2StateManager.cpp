#include "R2StateManager.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

R2StateManager& R2StateManager::GetInstance() {
    static R2StateManager Instance;
    return Instance;
}

void R2StateManager::SetAppId(int AppId) {
    mAppId = AppId;
}

int R2StateManager::GetAppId() const {
    return mAppId;
}

void R2StateManager::SetConfig(const Core::Config::EmulatorConfig& Config) {
    // TODO: validate Config before assigning
    mConfig = Config;
}

Core::Config::EmulatorConfig& R2StateManager::GetConfig() {
    return mConfig;
}

} // namespace Uues::EmuR2
