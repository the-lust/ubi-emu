#include "DbDataStateManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuDbData {
using namespace Uues::Core;

DbDataStateManager& DbDataStateManager::GetInstance() {
    static DbDataStateManager Instance;
    return Instance;
}

void DbDataStateManager::SetConfig(const Config::EmulatorConfig& Config) {
    mConfig = Config;
    mInitialized = true;
    Log::Logger::GetInstance().Info("[DbDataState] Config loaded, user='" +
        mConfig.UserName + "'");
}

Config::EmulatorConfig& DbDataStateManager::GetConfig() { return mConfig; }

bool DbDataStateManager::IsInitialized() const { return mInitialized; }

void DbDataStateManager::Reset() {
    mConfig = Config::EmulatorConfig::LoadDefaults();
    mInitialized = false;
    Log::Logger::GetInstance().Info("[DbDataState] Reset to defaults");
}

} // namespace Uues::EmuDbData
