#pragma once

#include "EmulatorInterface.hpp"
#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::Shared {

class EmulatorBase : public EmulatorInterface {
public:
    EmulatorBase();
    ~EmulatorBase() override;

    bool Initialize() override;
    bool Shutdown() override;
    bool IsInitialized() const override;
    bool LoadConfig(const Core::Common::String& ConfigPath) override;
    Core::Common::String GetName() const override { return "UUES Emulator"; }
    Core::Common::String GetVersion() const override { return "1.0.0.0"; }

protected:
    virtual bool OnInitialize();
    virtual bool OnShutdown();
    virtual bool OnLoadConfig(const Core::Ini::IniParser& Parser);

    bool mInitialized;
    Core::Config::EmulatorConfig mConfig;
    Core::Ini::IniParser mConfigParser;
    Core::Common::String mConfigPath;
};

} // namespace Uues::Shared