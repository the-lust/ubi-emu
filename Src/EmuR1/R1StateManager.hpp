#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuR1 {

class R1StateManager {
public:
    static R1StateManager& GetInstance();

    void SetAppId(int AppId);
    int GetAppId() const;
    void SetConfig(const Core::Config::EmulatorConfig& Config);
    Core::Config::EmulatorConfig& GetConfig();
    const Core::Config::EmulatorConfig& GetConfig() const;

private:
    R1StateManager() = default;
    R1StateManager(const R1StateManager&) = delete;
    R1StateManager& operator=(const R1StateManager&) = delete;

    int mAppId = 0; // default to 0 - games should set this
    Core::Config::EmulatorConfig mConfig; // TODO: maybe make this a pointer for lazy loading
};

} // namespace Uues::EmuR1