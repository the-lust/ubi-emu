#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuOrbit {

class OrbitConfigReader {
public:
    static bool ReadConfig(const Core::Ini::IniParser& Parser, Core::Config::EmulatorConfig& Config);
};

} // namespace Uues::EmuOrbit