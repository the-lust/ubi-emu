#include "UpcLoader.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

bool UpcLoader::Initialize() {
    if (mInitialized) return true;
    Log::Logger::GetInstance().Info("[UpcLoader] Initializing UPC Emulator");

    if (!mConfigLoaded) {
        Log::Logger::GetInstance().Warning("[UpcLoader] No config loaded, using defaults");
    }

    // FIXME: should verify that sub-systems are ready
    mInitialized = true;
    Log::Logger::GetInstance().Info("[UpcLoader] Initialization complete");
    return true;
}

bool UpcLoader::Shutdown() {
    if (!mInitialized) return true;
    Log::Logger::GetInstance().Info("[UpcLoader] Shutting down");
    mInitialized = false;
    return true;
}

bool UpcLoader::IsInitialized() const { return mInitialized; }
Common::String UpcLoader::GetName() const { return "UpcLoader"; }
Common::String UpcLoader::GetVersion() const { return "1.0.0.0"; }

bool UpcLoader::LoadConfig(const Common::String& ConfigPath) {
    mConfigPath = ConfigPath;
    mConfigLoaded = true;
    Log::Logger::GetInstance().Debug("[UpcLoader] Config path set: " + ConfigPath);
    return true;
}

} // namespace Uues::EmuUPC
