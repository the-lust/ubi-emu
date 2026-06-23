#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuDbData {

class DbDataConfigReader {
public:
    static bool ReadConfig(const Core::Ini::IniParser& Parser, Core::Config::EmulatorConfig& Config);
};

} // namespace Uues::EmuDbData