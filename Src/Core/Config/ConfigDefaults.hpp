#pragma once

#include "../Ini/IniParser.hpp"

namespace Uues::Core::Config {

class ConfigDefaults {
public:
    static Ini::IniParser CreateDefaultConfig();
    static Ini::IniParser CreateR1Defaults();
    static Ini::IniParser CreateR2Defaults();
    static Ini::IniParser CreateUpcDefaults();
    static Ini::IniParser CreateOrbitDefaults();
    static Ini::IniParser CreateDbDataDefaults();

private:
    ConfigDefaults() = delete;
    static void AddCommonSettings(Ini::IniParser& Parser);
};

} // namespace Uues::Core::Config