#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuOrbit {

class OrbitStateManager {
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