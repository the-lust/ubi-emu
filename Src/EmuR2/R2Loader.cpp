#include "R2Loader.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

bool R2Loader::Initialize() {
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[R2Loader] Already initialized, skipping");
        return true;
    }
    Log::Logger::GetInstance().Info("[R2Loader] Initializing Uplay R2 Emulator");
    mInitialized = true;
    return true;
}

bool R2Loader::Shutdown() {
    mInitialized = false;
    // TODO: cleanup resources
    return true;
}
bool R2Loader::IsInitialized() const {
    bool result = mInitialized;
    return result;
}
Common::String R2Loader::GetName() const {
    return "UplayR2Loader";
}
Common::String R2Loader::GetVersion() const {
    return "1.0.0.0";
}
bool R2Loader::LoadConfig(const Common::String& ConfigPath) {
    mConfigPath = ConfigPath;
    // TODO: actually validate the config path
    return true;
}

} // namespace Uues::EmuR2
