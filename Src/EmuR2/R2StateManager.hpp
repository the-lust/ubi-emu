#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuR2 {

class R2StateManager {
public:
    static R2StateManager& GetInstance();
    void SetAppId(int AppId);
    int GetAppId() const;
    void SetConfig(const Core::Config::EmulatorConfig& Config);
    Core::Config::EmulatorConfig& GetConfig();

private:
    R2StateManager() = default;
    R2StateManager(const R2StateManager&) = delete;
    int mAppId = 0; // TODO: should this be unsigned?
    Core::Config::EmulatorConfig mConfig;
};

} // namespace Uues::EmuR2