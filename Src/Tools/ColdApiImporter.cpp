#include "ColdApiImporter.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::Tools {
using namespace Uues::Core;

// TODO: implement ColdAPI import
// ColdAPI uses custom key names we need to map.

bool ColdApiImporter::Import(const Ini::IniParser& Source, Ini::IniParser& Output) {
    Log::Logger::GetInstance().Warning("[ColdApiImporter] Stub — ColdAPI config conversion pending");

    if (!Source.HasSection("ColdAPI") && !Source.HasSection("coldapi")) {
        Log::Logger::GetInstance().Warning("[ColdApiImporter] No ColdAPI section found in source");
    }

    Output.AddSection(Ini::IniSection("Settings"));
    Output.SetValue("Settings", "importer", "ColdApiImporter");
    Output.SetValue("Settings", "status", "placeholder");

    return true;
}

} // namespace Uues::Tools
