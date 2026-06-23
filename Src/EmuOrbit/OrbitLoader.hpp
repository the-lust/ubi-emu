#pragma once

#include "../Shared/EmulatorInterface.hpp"

#ifdef _WIN32
    #ifdef EmuOrbit_EXPORTS
        #define EMUORBIT_API __declspec(dllexport)
    #else
        #define EMUORBIT_API __declspec(dllimport)
    #endif
#else
    #define EMUORBIT_API
#endif

namespace Uues::EmuOrbit {

class EMUORBIT_API OrbitLoader : public Shared::EmulatorInterface {
public:
    bool Initialize() override;
    bool Shutdown() override;
    bool IsInitialized() const override;
    Core::Common::String GetName() const override;
    Core::Common::String GetVersion() const override;
    bool LoadConfig(const Core::Common::String& ConfigPath) override;
private:
    bool mInitialized = false;
    Core::Common::String mConfigPath;
};

} // namespace Uues::EmuOrbit