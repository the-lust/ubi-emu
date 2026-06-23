#pragma once

#include "../Shared/EmulatorInterface.hpp"

namespace Uues::EmuUPC {

class UpcLoader : public Shared::EmulatorInterface {
public:
    bool Initialize() override;
    bool Shutdown() override;
    bool IsInitialized() const override;
    Core::Common::String GetName() const override;
    Core::Common::String GetVersion() const override;
    bool LoadConfig(const Core::Common::String& ConfigPath) override;
private:
    bool mInitialized   = false;
    bool mConfigLoaded  = false;
    Core::Common::String mConfigPath;
};

} // namespace Uues::EmuUPC