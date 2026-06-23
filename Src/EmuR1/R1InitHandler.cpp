#include "R1InitHandler.hpp"
#include "R1StateManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

bool R1InitHandler::mInitialized = false;

bool R1InitHandler::HandleInit(unsigned int Version, int AppId) {
    // TODO: should we re-init if already initialized?
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[R1Init] Already initialized, skipping");
        return true;
    }
    auto& state = R1StateManager::GetInstance();
    state.SetAppId(AppId);
    mInitialized = true;
    Log::Logger::GetInstance().Info("[R1Init] Initialized with AppId=" + std::to_string(AppId));
    return true;
}

bool R1InitHandler::HandleShutdown() {
    if (!mInitialized) return true; // already shut down
    mInitialized = false;
    Log::Logger::GetInstance().Info("[R1Init] Shutdown complete");
    return true;
}

bool R1InitHandler::IsInitialized() { return mInitialized; }

} // namespace Uues::EmuR1
