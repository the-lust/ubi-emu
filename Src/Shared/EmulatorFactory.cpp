#include "EmulatorFactory.hpp"
#include "../EmuR1/R1Loader.hpp"
#include "../EmuR2/R2Loader.hpp"
#include "../EmuUPC/UpcLoader.hpp"
#include "../EmuOrbit/OrbitLoader.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Common/StringUtils.hpp"

// Emulator-to-class mapping:
//   "r1" / "uplay_r1"  -> R1Loader
//   "r2" / "uplay_r2"  -> R2Loader
//   "upc"              -> UpcLoader
//   "orbit"            -> OrbitLoader

namespace Uues::Shared {
using namespace Uues::Core;

std::unique_ptr<EmulatorInterface> EmulatorFactory::CreateEmulator(const Common::String& Type) {
    auto Lower = Common::StringUtils::ToLower(Type);
    if (Lower == "r1" || Lower == "uplay_r1") return CreateR1();
    if (Lower == "r2" || Lower == "uplay_r2") return CreateR2();
    if (Lower == "upc" || Lower == "uplay_upc") return CreateUPC();  // alias for compat
    if (Lower == "orbit" || Lower == "ubiorbit") return CreateOrbit();
    // Unknown type, return null but log a warning. Caller should handle this gracefully.
    Log::Logger::GetInstance().Warning("[EmuFactory] Unknown emulator type: " + Type + " — did you misspell it?");
    return nullptr;
}

std::unique_ptr<EmulatorInterface> EmulatorFactory::CreateR1() {
    return std::make_unique<EmuR1::R1Loader>();
}

std::unique_ptr<EmulatorInterface> EmulatorFactory::CreateR2() {
    return std::make_unique<EmuR2::R2Loader>();
}

std::unique_ptr<EmulatorInterface> EmulatorFactory::CreateUPC() {
    return std::make_unique<EmuUPC::UpcLoader>();
}

std::unique_ptr<EmulatorInterface> EmulatorFactory::CreateOrbit() {
    return std::make_unique<EmuOrbit::OrbitLoader>();
}

bool EmulatorFactory::RegisterEmulator([[maybe_unused]] const Common::String& Type, std::unique_ptr<EmulatorInterface> Emulator) {
    // TODO: implement dynamic registration for plugin-style emulators
    // For now this is a no-op, we use static linking
    Log::Logger::GetInstance().Warning("[EmuFactory] RegisterEmulator called but dynamic registration is not yet implemented");
    return false;
}

// FUTURE: add version gate here so old configs don't try to load unsupported emulators
// bool EmulatorFactory::CheckVersion(const Common::String& Type, int MinVersion) { ... }

} // namespace Uues::Shared
