#include "UnlockerJsonImporter.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::Tools {
using namespace Uues::Core;

// TODO: implement JSON parsing for Unlocker files
// The JSON library isn't linked yet, so this is a placeholder.

bool UnlockerJsonImporter::Import(const Ini::IniParser& Source, Ini::IniParser& Output) {
    Log::Logger::GetInstance().Warning("[UnlockerJsonImporter] Stub — JSON import not implemented yet");

    Output.AddSection(Ini::IniSection("Settings"));
    Output.SetValue("Settings", "source", "unlocker_json");
    Output.SetValue("Settings", "import_state", "placeholder");

    if (Source.HasSection("unlocker")) {
        auto& S = Source.GetSection("unlocker");
        for (auto& [K, V] : S.GetEntries()) {
            Output.SetValue("Settings", K, V);
        }
    }

    return true;
}

} // namespace Uues::Tools
