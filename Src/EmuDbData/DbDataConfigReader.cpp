#include "DbDataConfigReader.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuDbData {
using namespace Uues::Core;

bool DbDataConfigReader::ReadConfig(const Ini::IniParser& Parser, Config::EmulatorConfig& Config) {
    Log::Logger::GetInstance().Info("[DbDataConfig] Reading DbData config");

    if (!Parser.HasSection("dbdata")) {
        Log::Logger::GetInstance().Warning("[DbDataConfig] No [dbdata] section, using defaults");
        return true;
    }

    auto& Sec = Parser.GetSection("dbdata");
    Config.TokenFilePath = Sec.GetValue("token_file", Config.TokenFilePath);
    Config.Ticket = Sec.GetValue("ticket", Config.Ticket);
    Config.OwnershipToken = Sec.GetValue("ownership", Config.OwnershipToken);

    auto OwnAll = Sec.GetValue("unlock_all", "1");
    Config.UnlockAllDlc = (OwnAll == "1");

    if (Parser.HasSection("dbdata.dlc")) {
        auto& DlcSec = Parser.GetSection("dbdata.dlc");
        auto Entries = DlcSec.GetEntries();
        for (auto& [Key, Val] : Entries) {
            if (Val == "1") Config.Dlcs.push_back(Key);
        }
    }

    Log::Logger::GetInstance().Info("[DbDataConfig] Loaded " +
        std::to_string(Config.Dlcs.size()) + " DLC entries");
    return true;
}

} // namespace Uues::EmuDbData