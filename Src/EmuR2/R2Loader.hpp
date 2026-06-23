#pragma once

#include "../Shared/EmulatorInterface.hpp"

namespace Uues::EmuR2 {

class R2Loader : public Shared::EmulatorInterface {
public:
    bool Initialize() override;
    bool Shutdown() override;
    bool IsInitialized() const override;
    Core::Common::String GetName() const override;
    Core::Common::String GetVersion() const override;
    bool LoadConfig(const Core::Common::String& ConfigPath) override;

private:
    bool mInitialized = false;
    Core::Common::String mConfigPath; // path to config file, may be empty
};

} // namespace Uues::EmuR2