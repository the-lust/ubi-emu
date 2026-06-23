#include "DbDataInitHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuDbData {
using namespace Uues::Core;

bool DbDataInitHandler::mInitialized = false;
Common::String DbDataInitHandler::mConfigString;

bool DbDataInitHandler::HandleInit(const char* Config) {
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[DbDataInit] Already initialized, ignoring");
        return true;
    }
    if (!Config) {
        Log::Logger::GetInstance().Error("[DbDataInit] Null config pointer");
        return false;
    }
    mConfigString = Config;
    Log::Logger::GetInstance().Info("[DbDataInit] Initialized with config (" +
        std::to_string(mConfigString.size()) + " chars)");
    mInitialized = true;
    return true;
}

bool DbDataInitHandler::HandleShutdown() {
    if (!mInitialized) {
        Log::Logger::GetInstance().Warning("[DbDataInit] Shutdown before init, no-op");
        return false;
    }
    Log::Logger::GetInstance().Info("[DbDataInit] Shutdown");
    mInitialized = false;
    mConfigString.clear();
    return true;
}

bool DbDataInitHandler::IsInitialized() { return mInitialized; }

} // namespace Uues::EmuDbData
