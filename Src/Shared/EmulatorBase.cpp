#include "EmulatorBase.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Common/FileUtils.hpp"

namespace Uues::Shared {
using namespace Uues::Core;

// NOTE: mInitialized tracks three states: false (uninit), true (ready), and we
//       don't have a separate "failed" state yet, might want to add that later
EmulatorBase::EmulatorBase() : mInitialized(false) {}
EmulatorBase::~EmulatorBase() = default;

bool EmulatorBase::Initialize() {
    if (mInitialized) {
        Log::Logger::GetInstance().Warning("[EmuBase] Initialize called but already initialized — double-init guard");
        return true;
    }
    if (!mConfigPath.empty()) LoadConfig(mConfigPath);
    if (!OnInitialize()) {
        Log::Logger::GetInstance().Error("[EmuBase] OnInitialize failed for " + GetName());
        return false;
    }
    mInitialized = true;
    Log::Logger::GetInstance().Info("[EmuBase] " + GetName() + " initialized successfully");
    return true;
}

bool EmulatorBase::Shutdown() {
    if (!mInitialized) {
        Log::Logger::GetInstance().Warning("[EmuBase] Shutdown called but was never initialized — ignoring");
        return true;
    }
    Log::Logger::GetInstance().Info("[EmuBase] " + GetName() + " shutting down...");
    mInitialized = false;
    OnShutdown();
    return true;
}

bool EmulatorBase::IsInitialized() const { return mInitialized; }

bool EmulatorBase::LoadConfig(const Common::String& Path) {
    mConfigPath = Path;
    if (!mConfigParser.Load(Path)) {
        Log::Logger::GetInstance().Warning("[EmuBase] Could not load config: " + Path);
        return false;
    }
    mConfig.LoadFromIni(mConfigParser);
    Log::Logger::GetInstance().Info("[EmuBase] Config loaded from: " + Path);
    return OnLoadConfig(mConfigParser);
}

// --- overridable hooks, subclasses should override these ---
// NOTE: these return true by default so that emulators that don't need
//       custom init/shutdown/config logic don't have to implement them
bool EmulatorBase::OnInitialize() {
    Log::Logger::GetInstance().Warning("[EmuBase] OnInitialize not implemented — using default (no-op)");
    return true;
}
bool EmulatorBase::OnShutdown() {
    Log::Logger::GetInstance().Warning("[EmuBase] OnShutdown not implemented — using default (no-op)");
    return true;
}
bool EmulatorBase::OnLoadConfig(const Core::Ini::IniParser& Parser) {
    // default: config already loaded into mConfig, nothing extra needed
    return true;
}

} // namespace Uues::Shared
