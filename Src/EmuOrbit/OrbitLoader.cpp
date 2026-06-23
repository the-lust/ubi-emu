#include "OrbitLoader.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Common/FileUtils.hpp"

namespace Uues::EmuOrbit {
using namespace Uues::Core;

bool OrbitLoader::Initialize() {
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[OrbitLoader] Already initialized");
        return true;
    }

    Log::Logger::GetInstance().Info("[OrbitLoader] Initializing Orbit Emulator (v" + GetVersion() + ")");

    // verify config path exists, or use fallback
    if (!mConfigPath.empty() && !FileUtils::FileExists(mConfigPath)) {
        Log::Logger::GetInstance().Warning("[OrbitLoader] Config not found at '" +
            mConfigPath + "', will try defaults");
    }

    mInitialized = true;
    return true;
}

bool OrbitLoader::Shutdown() {
    if (!mInitialized) {
        Log::Logger::GetInstance().Warning("[OrbitLoader] Shutdown called before init");
        return false;
    }
    Log::Logger::GetInstance().Info("[OrbitLoader] Shutdown");
    mInitialized = false;
    return true;
}

bool OrbitLoader::IsInitialized() const { return mInitialized; }
Common::String OrbitLoader::GetName() const { return "OrbitLoader"; }
Common::String OrbitLoader::GetVersion() const { return "1.1.0.0"; }

bool OrbitLoader::LoadConfig(const Common::String& ConfigPath) {
    if (ConfigPath.empty()) {
        Log::Logger::GetInstance().Warning("[OrbitLoader] Empty config path");
        return false;
    }
    mConfigPath = ConfigPath;
    Log::Logger::GetInstance().Info("[OrbitLoader] Config path set to '" + ConfigPath + "'");
    return true;
}

} // namespace Uues::EmuOrbit
