#include "UpcInitHandler.hpp"
#include "UpcStateManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

bool UpcInitHandler::mInitialized = false;
int  UpcInitHandler::mAppId = 0;
unsigned int UpcInitHandler::mVersion = 0;

bool UpcInitHandler::HandleInit(unsigned int version, int AppId) {
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[UPCInit] Already initialized, ignoring");
        return true;
    }
    if (AppId <= 0) {
        Log::Logger::GetInstance().Error("[UPCInit] Invalid AppId: " + std::to_string(AppId));
        return false;
    }
    mAppId = AppId;
    mVersion = version;
    UpcStateManager::GetInstance().SetAppId(AppId);
    mInitialized = true;
    Log::Logger::GetInstance().Info("[UPCInit] Initialized AppId=" + std::to_string(AppId) +
        " Version=" + std::to_string(version));
    return true;
}

bool UpcInitHandler::HandleShutdown() {
    if (!mInitialized) return true; // already shut down
    mInitialized = false;
    Log::Logger::GetInstance().Info("[UPCInit] Shutdown");
    return true;
}

bool UpcInitHandler::IsInitialized() { return mInitialized; }

unsigned int UpcInitHandler::GetVersion() { return mVersion; }

} // namespace Uues::EmuUPC
