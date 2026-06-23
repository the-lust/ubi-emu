#include "LumaPlayImporter.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::Tools {
using namespace Uues::Core;

// TODO: implement LumaPlay .ini -> UUES ini conversion
// The LumaPlay format has different key names that need mapping.

bool LumaPlayImporter::Import(const Ini::IniParser& Source, Ini::IniParser& Output) {
    Log::Logger::GetInstance().Warning("[LumaPlayImporter] Not yet implemented — copying source sections verbatim");

    if (Source.HasSection("LumaPlay")) {
        auto& Luma = Source.GetSection("LumaPlay");
        Output.AddSection(Ini::IniSection("Settings"));
        for (auto& [K, V] : Luma.GetEntries()) {
            Common::String MappedKey = K;
            // basic key remapping (incomplete)
            if (K == "appid") MappedKey = "game_id";
            else if (K == "lang") MappedKey = "language";
            else if (K == "savepath") MappedKey = "save_directory";
            Output.SetValue("Settings", MappedKey, V);
        }
    } else {
        Output.AddSection(Ini::IniSection("Settings"));
    }

    return true;
}

} // namespace Uues::Tools
