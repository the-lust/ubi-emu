#include "R1StateManager.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

// singleton - initialized on first use
R1StateManager& R1StateManager::GetInstance() {
    static R1StateManager instance;
    return instance;
}

void R1StateManager::SetAppId(int AppId) {
    mAppId = AppId;
}

int R1StateManager::GetAppId() const {
    return mAppId;
}

void R1StateManager::SetConfig(const Config::EmulatorConfig& Config) {
    mConfig = Config;
}

Config::EmulatorConfig& R1StateManager::GetConfig() {
    return mConfig;
}

const Config::EmulatorConfig& R1StateManager::GetConfig() const {
    return mConfig;
}

} // namespace Uues::EmuR1
