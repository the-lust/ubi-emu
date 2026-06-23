#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuR1 {

class R1ConfigReader {
public:
    R1ConfigReader();
    ~R1ConfigReader();

    bool Load(const Core::Common::String& Path);
    bool LoadFromIni(const Core::Ini::IniParser& Parser);
    Core::Config::EmulatorConfig GetConfig() const;

private:
    Core::Config::EmulatorConfig mConfig; // loaded config data
};

} // namespace Uues::EmuR1