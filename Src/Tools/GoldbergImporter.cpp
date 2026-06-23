#include "GoldbergImporter.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::Tools {
using namespace Uues::Core;

// TODO: actually implement Goldberg -> UUES format conversion
// The Goldberg emulator uses different INI keys, we need a mapping table here.

bool GoldbergImporter::Import(const Core::Ini::IniParser& Source, Core::Ini::IniParser& Output) {
    Log::Logger::GetInstance().Warning("[GoldbergImporter] Not yet implemented — call will be ignored");

    // copy the whole source as a new section so nothing is lost
    Output.AddSection("Settings");
    for (auto& Name : Source.GetSectionNames()) {
        Output.AddSection(Source.GetSection(Name));
    }

    Log::Logger::GetInstance().Info("[GoldbergImporter] Copied " +
        std::to_string(Source.GetSectionCount()) + " section(s) verbatim");

    return true;
}

} // namespace Uues::Tools
