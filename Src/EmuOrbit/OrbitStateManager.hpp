#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

#ifdef _WIN32
    #ifdef EmuOrbit_EXPORTS
        #define EMUORBIT_API __declspec(dllexport)
    #else
        #define EMUORBIT_API
    #endif
#else
    #define EMUORBIT_API
#endif

namespace Uues::EmuOrbit {

class EMUORBIT_API OrbitStateManager {
public:
    static OrbitStateManager& GetInstance();
    void SetAppId(int AppId);
    int GetAppId() const;
    void SetConfig(const Core::Config::EmulatorConfig& Config);
    Core::Config::EmulatorConfig& GetConfig();
    void Reset();
private:
    OrbitStateManager() = default;
    OrbitStateManager(const OrbitStateManager&) = delete;
    int mAppId = 0;
    Core::Config::EmulatorConfig mConfig;
};

} // namespace Uues::EmuOrbit