#include "ConfigDefaults.hpp"
#include "../Common/Constants.hpp"

namespace Uues::Core::Config {

void ConfigDefaults::AddCommonSettings(Ini::IniParser& Parser) {
    // defaults chosen to match typical user setup, override as needed
    Parser.SetValue("Settings", "UserName", Common::Defaults::UserName);
    Parser.SetValue("Settings", "UserId", Common::UplayIds::DefaultUserId);
    Parser.SetValue("Settings", "Email", Common::Defaults::Email);
    Parser.SetValue("Settings", "Language", Common::Defaults::Language);
    Parser.SetValue("Settings", "LogLevel", "info");
    Parser.SetValue("Settings", "DebugMode", "false");
    Parser.SetValue("Settings", "SaveType", "0");
    Parser.SetValue("Settings", "SavePath", Common::Defaults::SaveRoot);
    Parser.SetValue("Settings", "UnlockAllDlc", "true");
    Parser.SetValue("Settings", "UnlockAllItems", "true");
    Parser.SetValue("Settings", "OfflineMode", "true");
    Parser.SetValue("Settings", "LanMode", "true");
    Parser.SetValue("Settings", "EnableAchievements", "true");
    Parser.SetValue("Settings", "EnableOverlay", "true");
}

Ini::IniParser ConfigDefaults::CreateDefaultConfig() {
    Ini::IniParser Parser;
    AddCommonSettings(Parser);
    return Parser;
}

Ini::IniParser ConfigDefaults::CreateR1Defaults() {
    auto Parser = CreateDefaultConfig();
    Parser.SetValue("Settings", "GenerateNewId", "true");
    Parser.SetValue("DLC", "; Add DLC IDs here, one per line", "");
    return Parser;
}

Ini::IniParser ConfigDefaults::CreateR2Defaults() {
    auto Parser = CreateDefaultConfig();
    Parser.SetValue("Settings", "GenerateNewId", "true");
    // HACK: using a value with a semicolon prefix as a comment in the INI
    Parser.SetValue("DLC", "; Add DLC IDs here, one per line", "");
    Parser.SetValue("Items", "; Add Item IDs here, one per line", "");
    return Parser;
}

Ini::IniParser ConfigDefaults::CreateUpcDefaults() {
    auto Parser = CreateDefaultConfig();
    Parser.SetValue("Network", "ServerUrl", "http://localhost");
    Parser.SetValue("Network", "ServerPort", "80");
    Parser.SetValue("Network", "PipeName", "UPC_Demux");
    return Parser;
}

Ini::IniParser ConfigDefaults::CreateOrbitDefaults() {
    auto Parser = CreateDefaultConfig();
    Parser.SetValue("Settings", "AccountId", "0");
    Parser.SetValue("Network", "ServerIP", "127.0.0.1");
    Parser.SetValue("Network", "ServerPort", "34000");
    return Parser;
}

Ini::IniParser ConfigDefaults::CreateDbDataDefaults() {
    auto Parser = CreateDefaultConfig();
    Parser.SetValue("Ticket", "Ticket", "");
    Parser.SetValue("Ticket", "Ownership", "");
    Parser.SetValue("Ticket", "TokenFile", "Token.ini");
    Parser.SetValue("Settings", "Dlcs", "");
    Parser.SetValue("Settings", "AppId", "");
    return Parser;
}

} // namespace Uues::Core::Config