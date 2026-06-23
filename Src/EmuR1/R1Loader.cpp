#include "R1Loader.hpp"
#include "R1ConfigReader.hpp"
#include "R1StateManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

bool R1Loader::Initialize() {
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[R1Loader] Already initialized, skipping");
        return true;
    }

    Log::Logger::GetInstance().Info("[R1Loader] Initializing Uplay R1 Emulator");

    // load config if a path was specified
    if (!mConfigPath.empty()) {
        R1ConfigReader reader;
        if (reader.Load(mConfigPath)) {
            auto& State = R1StateManager::GetInstance();
            State.SetConfig(reader.GetConfig());
        } else {
            Log::Logger::GetInstance().Warning("[R1Loader] Failed to load config, using defaults");
        }
    }

    mInitialized = true;
    Log::Logger::GetInstance().Info("[R1Loader] Uplay R1 Emulator initialized successfully");
    return true;
}

bool R1Loader::Shutdown() {
    mInitialized = false;
    Log::Logger::GetInstance().Info("[R1Loader] Uplay R1 Emulator shut down");
    return true;
}

bool R1Loader::IsInitialized() const { return mInitialized; }

Common::String R1Loader::GetName() const { return "UplayR1Loader"; }

Common::String R1Loader::GetVersion() const { return "1.0.0.0"; }

bool R1Loader::LoadConfig(const Common::String& ConfigPath) {
    if (ConfigPath.empty()) {
        Log::Logger::GetInstance().Warning("[R1Loader] Empty config path!");
        return false;
    }
    mConfigPath = ConfigPath;
    return true;
}

} // namespace Uues::EmuR1
