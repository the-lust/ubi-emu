#include "OrbitConfigReader.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuOrbit {
using namespace Uues::Core;

bool OrbitConfigReader::ReadConfig(const Ini::IniParser& Parser, Config::EmulatorConfig& Config) {
    Log::Logger::GetInstance().Info("[OrbitConfig] Reading Orbit config");

    if (!Parser.HasSection("orbit")) {
        Log::Logger::GetInstance().Warning("[OrbitConfig] Missing [orbit] section, using defaults");
        return true;
    }

    auto& Section = Parser.GetSection("orbit");
    Config.UserName = Section.GetValue("username", Config.UserName);
    Config.SavePath = Section.GetValue("save_path", Config.SavePath);
    Config.DebugMode = (Section.GetValue("debug", "0") == "1");

    Log::Logger::GetInstance().Info("[OrbitConfig] User: " + Config.UserName);

    if (Parser.HasSection("orbit.dlc")) {
        auto& DlcSection = Parser.GetSection("orbit.dlc");
        auto Entries = DlcSection.GetEntries();
        for (auto& [Key, Val] : Entries) {
            if (Val == "1") {
                Config.Dlcs.push_back(Key);
            }
        }
    }

    return true;
}

} // namespace Uues::EmuOrbit