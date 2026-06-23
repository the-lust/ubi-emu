#pragma once

#include "../Common/Types.hpp"
#include "../Ini/IniParser.hpp"

namespace Uues::Core::Config {

enum class EmulatorType {
    R1,
    R2,
    Upc,
    Orbit,
    DbData,
    Unknown
};

struct EmulatorConfig {
    // General
    EmulatorType Type;
    Common::String UserName;
    Common::String UserId;
    Common::String Email;
    Common::String Language;
    Common::String LogLevel;
    bool DebugMode;

    // Save
    int SaveType;
    Common::String SavePath;
    Common::String SaveDirectory;

    // DLC
    Common::StringList Dlcs;
    Common::StringList Items;
    bool UnlockAllDlc;
    bool UnlockAllItems;

    // Network
    Common::String ServerUrl;
    uint16_t ServerPort;
    Common::String PipeName;
    bool LanMode;
    bool OfflineMode;

    // Ticket
    Common::String Ticket;
    Common::String OwnershipToken;
    Common::String TokenFilePath;

    // Overlay
    bool EnableOverlay;
    bool EnableAchievements;

    static EmulatorConfig LoadDefaults();
    bool LoadFromIni(const Ini::IniParser& Parser);
    void SaveToIni(Ini::IniParser& Parser) const;
};

} // namespace Uues::Core::Config