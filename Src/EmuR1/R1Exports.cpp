#include "R1Exports.hpp"
#include "R1StateManager.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Storage/AchievementManager.hpp"
#include "../Core/Common/StringUtils.hpp"
#include <cstring>

extern "C" {

int UPLAY_Init(unsigned int Version, int AppId) {
    auto& State = Uues::EmuR1::R1StateManager::GetInstance();
    State.SetAppId(AppId);
    Uues::Core::Log::Logger::GetInstance().Info("UPLAY_Init(Version=" +
        std::to_string(Version) + ", AppId=" + std::to_string(AppId) + ")");
    return 1;
}

int UPLAY_GetErrorCode() { return 0; }

int UPLAY_GetLastError(char* Buffer, unsigned int BufferSize) {
    if (Buffer && BufferSize > 0) Buffer[0] = '\0';
    return 0;
}

int UPLAY_USER_GetUsername(char* Buffer, unsigned int BufferSize) {
    auto Name = Uues::EmuR1::R1StateManager::GetInstance().GetConfig().UserName;
    strncpy_s(Buffer, BufferSize, Name.c_str(), BufferSize - 1);
    return 1;
}

int UPLAY_USER_GetUsernameUtf8(char* Buffer, unsigned int BufferSize) {
    return UPLAY_USER_GetUsername(Buffer, BufferSize);
}

int UPLAY_USER_GetEmail(char* Buffer, unsigned int BufferSize) {
    auto Email = Uues::EmuR1::R1StateManager::GetInstance().GetConfig().Email;
    strncpy_s(Buffer, BufferSize, Email.c_str(), BufferSize - 1);
    return 1;
}

int UPLAY_USER_GetPassword(char* Buffer, unsigned int BufferSize) {
    // we don't store passwords, so return empty
    if (Buffer && BufferSize > 0) Buffer[0] = '\0';
    return 0;
}

int UPLAY_USER_GetPasswordUtf8(char* Buffer, unsigned int BufferSize) {
    return UPLAY_USER_GetPassword(Buffer, BufferSize);
}

int UPLAY_USER_GetCredentials(char* Buffer, unsigned int BufferSize) {
    auto Creds = Uues::EmuR1::R1StateManager::GetInstance().GetConfig().Email + ":";
    strncpy_s(Buffer, BufferSize, Creds.c_str(), BufferSize - 1);
    return 1;
}

int UPLAY_ACH_GetAchievement(char* AchId, int* OutUnlocked) {
    if (OutUnlocked) *OutUnlocked = 0;
    return 0; // not implemented - achievements always locked
}

int UPLAY_ACH_SetAchievement(char* AchId) {
    Uues::Core::Log::Logger::GetInstance().Info("UPLAY_ACH_SetAchievement: " +
        (AchId ? std::string(AchId) : "null"));
    return 1;
}

int UPLAY_ACH_ResetAchievement(char* AchId) {
    return 1;
}

int UPLAY_DLC_IsInstalled(int DlcId, int* OutInstalled) {
    if (OutInstalled) *OutInstalled = 1;
    return 1;
}

int UPLAY_DLC_GetList(int* OutDlcIds, unsigned int* OutCount) {
    if (OutCount) *OutCount = 0;
    return 1;
}

int UPLAY_SAVE_GetSaveGame(char* SaveName, void* Buffer, unsigned int* BufferSize) {
    // TODO: read from actual save directory
    return 0;
}

int UPLAY_SAVE_SetSaveGame(char* SaveName, void* Buffer, unsigned int BufferSize) {
    // TODO: write to actual save directory
    return 1;
}

int UPLAY_OVERLAY_Show() { return 1; } // stub - overlay not rendered
int UPLAY_OVERLAY_Hide() { return 1; } // stub

int UPLAY_PARTY_Init() { return 1; }
int UPLAY_PARTY_Shutdown() { return 1; }

int UPLAY_AVATAR_GetAvatarIdForCurrentUser(char* OutAvatarId, unsigned int BufferSize) {
    if (OutAvatarId && BufferSize > 0) OutAvatarId[0] = '\0';
    return 1;
}

int UPLAY_AVATAR_GetBitmap(char* AvatarId, void* OutBitmap, unsigned int* OutSize) {
    return 0;
}

int UPLAY_FRIENDS_GetCount(unsigned int* OutCount) {
    // no friends in offline mode
    if (OutCount) *OutCount = 0;
    return 1;
}

int UPLAY_RICHPRESENCE_SetPresence(char* Presence) { return 1; } // silently ignored

int UPLAY_SetGameSession(unsigned int SessionId) { return 1; }
int UPLAY_ClearGameSession() { return 1; }

} // extern "C"
