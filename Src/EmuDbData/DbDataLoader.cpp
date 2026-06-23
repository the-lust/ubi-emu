#include "DbDataLoader.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Common/FileUtils.hpp"

namespace Uues::EmuDbData {
using namespace Uues::Core;

bool DbDataLoader::Initialize() {
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[DbDataLoader] Double-init, skipping");
        return true;
    }
    if (mConfigPath.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataLoader] No config loaded, initializing with defaults");
    } else if (!Common::FileUtils::Exists(mConfigPath)) {
        Log::Logger::GetInstance().Warning("[DbDataLoader] Config '" + mConfigPath + "' not found, continuing anyway");
    }
    Log::Logger::GetInstance().Info("[DbDataLoader] DbData Emulator v" + GetVersion() + " starting");
    mInitialized = true;
    return true;
}

bool DbDataLoader::Shutdown() {
    if (!mInitialized) return false;
    Log::Logger::GetInstance().Info("[DbDataLoader] Shutdown");
    mInitialized = false;
    return true;
}

bool DbDataLoader::IsInitialized() const { return mInitialized; }
Common::String DbDataLoader::GetName() const { return "DbDataLoader"; }
Common::String DbDataLoader::GetVersion() const { return "1.0.1.0"; }

bool DbDataLoader::LoadConfig(const Common::String& ConfigPath) {
    if (ConfigPath.empty()) return false;
    mConfigPath = ConfigPath;
    if (Common::FileUtils::Exists(ConfigPath)) {
        Log::Logger::GetInstance().Info("[DbDataLoader] Config loaded: " + ConfigPath);
    } else {
        Log::Logger::GetInstance().Warning("[DbDataLoader] Config path set but file missing: " + ConfigPath);
    }
    return true;
}

} // namespace Uues::EmuDbData
