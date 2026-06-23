#pragma once

#include "../Shared/EmulatorInterface.hpp"

#ifdef _WIN32
    #ifdef EmuR2_EXPORTS
        #define EMUR2_API __declspec(dllexport)
    #else
        #define EMUR2_API __declspec(dllimport)
    #endif
#else
    #define EMUR2_API
#endif

namespace Uues::EmuR2 {

class EMUR2_API R2Loader : public Shared::EmulatorInterface {
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