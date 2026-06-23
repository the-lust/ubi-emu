#include "EmulatorConfig.hpp"
#include "../Common/Constants.hpp"

namespace Uues::Core::Config {

EmulatorConfig EmulatorConfig::LoadDefaults() {
    EmulatorConfig Cfg{};
    Cfg.Type = EmulatorType::Unknown;
    Cfg.UserName = Common::Defaults::UserName;
    Cfg.UserId = Common::UplayIds::DefaultUserId;
    Cfg.Email = Common::Defaults::Email;
    Cfg.Language = Common::Defaults::Language;
    Cfg.LogLevel = "info";
    Cfg.DebugMode = false;
    Cfg.SaveType = 0;             // 0 = default save type
    Cfg.SavePath = Common::Defaults::SaveRoot;
    Cfg.UnlockAllDlc = true;       // unlock everything by default
    Cfg.UnlockAllItems = true;
    Cfg.LanMode = true;
    Cfg.OfflineMode = true;
    Cfg.EnableOverlay = true;
    Cfg.EnableAchievements = true;
    return Cfg;
}

bool EmulatorConfig::LoadFromIni(const Ini::IniParser& Parser) {
    // FIXME: if Settings section exists but is empty, we silently use defaults
    auto& S = Parser.GetSection("Settings");
    if (S.GetName().empty()) return false;

    UserName = S.HasKey("UserName") ? S.GetKey("UserName").GetValue().AsString() : Common::Defaults::UserName;
    UserId = S.HasKey("UserId") ? S.GetKey("UserId").GetValue().AsString() : Common::UplayIds::DefaultUserId;
    Email = S.HasKey("Email") ? S.GetKey("Email").GetValue().AsString() : Common::Defaults::Email;
    Language = S.HasKey("Language") ? S.GetKey("Language").GetValue().AsString() : Common::Defaults::Language;
    LogLevel = S.HasKey("LogLevel") ? S.GetKey("LogLevel").GetValue().AsString() : "info";
    DebugMode = S.HasKey("DebugMode") && S.GetKey("DebugMode").GetValue().AsBool(false);
    SaveType = S.HasKey("SaveType") ? S.GetKey("SaveType").GetValue().AsInt(0) : 0;
    SavePath = S.HasKey("SavePath") ? S.GetKey("SavePath").GetValue().AsString() : Common::Defaults::SaveRoot;
    UnlockAllDlc = S.HasKey("UnlockAllDlc") ? S.GetKey("UnlockAllDlc").GetValue().AsBool(true) : true;
    UnlockAllItems = S.HasKey("UnlockAllItems") ? S.GetKey("UnlockAllItems").GetValue().AsBool(true) : true;
    LanMode = S.HasKey("LanMode") ? S.GetKey("LanMode").GetValue().AsBool(true) : true;
    OfflineMode = S.HasKey("OfflineMode") ? S.GetKey("OfflineMode").GetValue().AsBool(true) : true;
    EnableOverlay = S.HasKey("EnableOverlay") ? S.GetKey("EnableOverlay").GetValue().AsBool(true) : true;
    EnableAchievements = S.HasKey("EnableAchievements") ? S.GetKey("EnableAchievements").GetValue().AsBool(true) : true;

    if (Parser.HasSection("DLC")) {
        auto& DlcSection = Parser.GetSection("DLC");
        for (auto& Key : DlcSection.GetAllKeys()) {
            Dlcs.push_back(Key.GetName());
        }
    }

    if (Parser.HasSection("Network")) {
        auto& NetSection = Parser.GetSection("Network");
        ServerUrl = NetSection.HasKey("ServerUrl") ? NetSection.GetKey("ServerUrl").GetValue().AsString() : "";
        ServerPort = NetSection.HasKey("ServerPort") ? static_cast<uint16_t>(NetSection.GetKey("ServerPort").GetValue().AsUint(0)) : 0;
        PipeName = NetSection.HasKey("PipeName") ? NetSection.GetKey("PipeName").GetValue().AsString() : "";
    }

    return true;
}

void EmulatorConfig::SaveToIni(Ini::IniParser& Parser) const {
    Parser.SetValue("Settings", "UserName", UserName);
    Parser.SetValue("Settings", "UserId", UserId);
    Parser.SetValue("Settings", "Email", Email);
    Parser.SetValue("Settings", "Language", Language);
    Parser.SetValue("Settings", "LogLevel", LogLevel);
    Parser.SetValue("Settings", "DebugMode", DebugMode ? "true" : "false");
    Parser.SetValue("Settings", "SaveType", std::to_string(SaveType));
    Parser.SetValue("Settings", "SavePath", SavePath);
    Parser.SetValue("Settings", "UnlockAllDlc", UnlockAllDlc ? "true" : "false");
    Parser.SetValue("Settings", "UnlockAllItems", UnlockAllItems ? "true" : "false");
    Parser.SetValue("Settings", "LanMode", LanMode ? "true" : "false");
    Parser.SetValue("Settings", "OfflineMode", OfflineMode ? "true" : "false");
    Parser.SetValue("Settings", "EnableAchievements", EnableAchievements ? "true" : "false");
}

} // namespace Uues::Core::Config