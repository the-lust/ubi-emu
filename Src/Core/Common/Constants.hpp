#pragma once

#include "Types.hpp"

namespace Uues::Core::Common {

namespace Limits {
    constexpr size_t MaxIniLineLength = 4096;
    constexpr size_t MaxIniSections = 512;
    constexpr size_t MaxIniKeysPerSection = 2048;
    constexpr size_t MaxPathLength = 260;
    constexpr size_t MaxBufferSize = 1024 * 1024 * 64;
    constexpr size_t MaxPacketSize = 1024 * 1024 * 16;
    constexpr size_t MaxNamedPipeBuffer = 4096;
    constexpr int MaxRetryAttempts = 3;
    constexpr int DefaultTimeoutMs = 5000;
}

namespace Defaults {
    constexpr const char* UserName = "Player";
    constexpr const char* Email = "player@local.host";
    constexpr const char* Language = "en-US";
    constexpr const char* SaveRoot = "SaveGames";
    constexpr const char* ConfigFileName = "Ubi.ini";
    constexpr const char* LogFileName = "Uues.log";
    constexpr const char* TicketFileName = "Token.ini";
}

namespace UplayIds {
    constexpr const char* AnonymousUserId = "00000000-0000-0000-0000-000000000000";
    constexpr const char* DefaultUserId = "80f33a39-e682-4d1f-b693-39267e890df2";
    constexpr const char* DefaultGameId = "66333333-e688-4d1f-b693-39267e890df2";
}

} // namespace Uues::Core::Common