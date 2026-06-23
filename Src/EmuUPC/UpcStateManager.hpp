#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuUPC {

class UpcStateManager {
public:
    static UpcStateManager& GetInstance();
    void SetAppId(int AppId);
    int GetAppId() const;
    void SetVersion(unsigned int Version);
    unsigned int GetVersion() const;
    void SetConfig(const Core::Config::EmulatorConfig& Config);
    Core::Config::EmulatorConfig& GetConfig();
private:
    UpcStateManager() = default;
    UpcStateManager(const UpcStateManager&) = delete;
    int mAppId = 0;
    unsigned int mVersion = 0;
    Core::Config::EmulatorConfig mConfig;
};

} // namespace Uues::EmuUPC