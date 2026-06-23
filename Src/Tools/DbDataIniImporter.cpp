#include "DbDataIniImporter.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::Tools {
using namespace Uues::Core;

// TODO: actually implement the INI -> DbData format conversion
// Currently just copies a placeholder section.

bool DbDataIniImporter::Import(const Ini::IniParser& Source, Ini::IniParser& Output) {
    Log::Logger::GetInstance().Warning("[DbDataIniImporter] Stub — real import not implemented, adding placeholder");

    Output.AddSection(Ini::IniSection("Ticket"));
    Output.SetValue("Ticket", "type", "ownership");
    Output.SetValue("Ticket", "source", "ini_import");

    if (Source.HasSection("Settings")) {
        auto& Settings = Source.GetSection("Settings");
        Output.AddSection(Settings);
    }

    return true;
}

} // namespace Uues::Tools
