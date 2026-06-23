#include "UpcStateManager.hpp"
#include <cassert>

namespace Uues::EmuUPC {
using namespace Uues::Core;

// not thread safe but games mostly call from one thread anyway
UpcStateManager& UpcStateManager::GetInstance() {
    static UpcStateManager Instance;
    return Instance;
}

void UpcStateManager::SetAppId(int id) {
    assert(id > 0 && "AppId should be positive");
    mAppId = id;
}
int UpcStateManager::GetAppId() const { return mAppId; }

void UpcStateManager::SetVersion(unsigned int v) { mVersion = v; }
unsigned int UpcStateManager::GetVersion() const { return mVersion; }

void UpcStateManager::SetConfig(const Core::Config::EmulatorConfig& Config) {
    mConfig = Config;
}
Core::Config::EmulatorConfig& UpcStateManager::GetConfig() {
    return mConfig;
}

} // namespace Uues::EmuUPC
