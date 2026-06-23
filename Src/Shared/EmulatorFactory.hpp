#pragma once

#include "EmulatorInterface.hpp"
#include "../Core/Common/Types.hpp"
#include <memory>

namespace Uues::Shared {

class EmulatorFactory {
public:
    static std::unique_ptr<EmulatorInterface> CreateEmulator(const Core::Common::String& Type);
    static std::unique_ptr<EmulatorInterface> CreateR1();
    static std::unique_ptr<EmulatorInterface> CreateR2();
    static std::unique_ptr<EmulatorInterface> CreateUPC();
    static std::unique_ptr<EmulatorInterface> CreateOrbit();
    static std::unique_ptr<EmulatorInterface> CreateDbData();

    static bool RegisterEmulator(const Core::Common::String& Type, std::unique_ptr<EmulatorInterface> Emulator);

private:
    EmulatorFactory() = delete;
};

} // namespace Uues::Shared