#pragma once

#include "../Core/Ini/IniParser.hpp"
#include "../Core/Common/Types.hpp"

namespace Uues::Tools {

class IniToUbiIniConverter {
public:
    static bool Convert(const Core::Ini::IniParser& Source, Core::Ini::IniParser& Output);
    static bool SaveToFile(Core::Ini::IniParser& Parser, const Core::Common::String& OutputPath);
};

} // namespace Uues::Tools