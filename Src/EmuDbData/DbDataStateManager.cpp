#include "DbDataStateManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuDbData {
using namespace Uues::Core;

DbDataStateManager& DbDataStateManager::GetInstance() {
    static DbDataStateManager Instance;
    return Instance;
}

void DbDataStateManager::SetConfig(const Core::Config::EmulatorConfig& Config) {
    mConfig = Config;
    mInitialized = true;
    Log::Logger::GetInstance().Info("[DbDataState] Config loaded, user='" +
        mConfig.UserName + "'");
}

Core::Config::EmulatorConfig& DbDataStateManager::GetConfig() { return mConfig; }

bool DbDataStateManager::IsInitialized() const { return mInitialized; }

void DbDataStateManager::Reset() {
    mConfig = Core::Config::EmulatorConfig::LoadDefaults();
    mInitialized = false;
    Log::Logger::GetInstance().Info("[DbDataState] Reset to defaults");
}

} // namespace Uues::EmuDbData
