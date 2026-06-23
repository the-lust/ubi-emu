#include "DllMain.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Log/ConsoleTarget.hpp"
#include "../Core/Log/DebugOutputTarget.hpp"
#include "../Core/Log/FileTarget.hpp"
#include "../Core/Common/FileUtils.hpp"

namespace Uues::Shared {
using namespace Uues::Core;

bool DllMain::OnProcessAttach(HINSTANCE Instance) {
    auto& Logger = Core::Log::Logger::GetInstance();
    Logger.AddTarget(std::make_unique<Core::Log::DebugOutputTarget>());
    Logger.AddTarget(std::make_unique<Core::Log::ConsoleTarget>());

    auto LogPath = Core::Common::FileUtils::CombinePath(
        Core::Common::FileUtils::GetModuleDirectory(), "Uues.log");
    auto FileTarget = std::make_unique<Core::Log::FileTarget>(LogPath);
    if (FileTarget->Open()) {
        Logger.AddTarget(std::move(FileTarget));
    }

    Logger.Info("UUES Emulator loaded");
    return true;
}

bool DllMain::OnProcessDetach(HINSTANCE Instance) {
    // Cleanup: flush logs, remove targets, order matters here
    auto& Logger = Core::Log::Logger::GetInstance();
    Logger.Info("UUES Emulator unloaded");
    Logger.RemoveAllTargets();
    // FIXME: possible race if other threads are still logging during detach
    return true;
}

// Thread attach/detach, most games don't need per-thread init,
// but we leave the hooks here in case a future emulator does
bool DllMain::OnThreadAttach(HINSTANCE Instance) {
    // Not much to do here, TLS setup if needed later
    return true;
}
bool DllMain::OnThreadDetach(HINSTANCE Instance) {
    // Could clean up per-thread log buffers here
    return true;
}

} // namespace Uues::Shared
