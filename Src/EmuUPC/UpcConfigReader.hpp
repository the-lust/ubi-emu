#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuUPC {

class UpcConfigReader {
public:
    static bool ReadConfig(const Core::Ini::IniParser& Parser, Core::Config::EmulatorConfig& Config);

    // TODO: implement section-level reading
    static bool ReadSection(const Core::Ini::IniParser& Parser, const Core::Common::String& Section);
};

} // namespace Uues::EmuUPC