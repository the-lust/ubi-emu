#pragma once

#include "../Core/Ini/IniParser.hpp"

namespace Uues::Tools {

class DbDataIniImporter {
public:
    static bool Import(const Core::Ini::IniParser& Source, Core::Ini::IniParser& Output);
};

} // namespace Uues::Tools