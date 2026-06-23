#pragma once

#include "../Shared/EmulatorInterface.hpp"

#ifdef _WIN32
    #ifdef EmuUPC_EXPORTS
        #define EMUUPC_API __declspec(dllexport)
    #else
        #define EMUUPC_API __declspec(dllimport)
    #endif
#else
    #define EMUUPC_API
#endif

namespace Uues::EmuUPC {

class EMUUPC_API UpcLoader : public Shared::EmulatorInterface {
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