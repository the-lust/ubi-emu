#pragma once

#include "../Shared/EmulatorInterface.hpp"

#ifdef _WIN32
    #ifdef EmuR1_EXPORTS
        #define EMUR1_API __declspec(dllexport)
    #else
        #define EMUR1_API __declspec(dllimport)
    #endif
#else
    #define EMUR1_API
#endif

namespace Uues::EmuR1 {

class EMUR1_API R1Loader : public Shared::EmulatorInterface {
public:
    bool Initialize() override;
    bool Shutdown() override;
    bool IsInitialized() const override;
    Core::Common::String GetName() const override;
    Core::Common::String GetVersion() const override;
    bool LoadConfig(const Core::Common::String& ConfigPath) override;

private:
    bool mInitialized = false; // TODO: make this atomic?
    Core::Common::String mConfigPath;
};

} // namespace Uues::EmuR1