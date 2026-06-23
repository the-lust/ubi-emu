#pragma once

#include "../Core/Common/Macros.hpp"

extern "C" {

UUES_EXPORT int UPLAY_Init(unsigned int Version, int AppId);
UUES_EXPORT int UPLAY_GetErrorCode();
UUES_EXPORT int UPLAY_GetLastError(char* Buffer, unsigned int BufferSize); // clears error

UUES_EXPORT int UPLAY_USER_GetUsername(char* Buffer, unsigned int BufferSize);
UUES_EXPORT int UPLAY_USER_GetUsernameUtf8(char* Buffer, unsigned int BufferSize);
UUES_EXPORT int UPLAY_USER_GetEmail(char* Buffer, unsigned int BufferSize);
UUES_EXPORT int UPLAY_USER_GetPassword(char* Buffer, unsigned int BufferSize);
UUES_EXPORT int UPLAY_USER_GetPasswordUtf8(char* Buffer, unsigned int BufferSize);
UUES_EXPORT int UPLAY_USER_GetCredentials(char* Buffer, unsigned int BufferSize);

UUES_EXPORT int UPLAY_ACH_GetAchievement(char* AchievementId, int* OutUnlocked);
UUES_EXPORT int UPLAY_ACH_SetAchievement(char* AchievementId);
UUES_EXPORT int UPLAY_ACH_ResetAchievement(char* AchievementId);

UUES_EXPORT int UPLAY_DLC_IsInstalled(int DlcId, int* OutInstalled);
UUES_EXPORT int UPLAY_DLC_GetList(int* OutDlcIds, unsigned int* OutCount);

UUES_EXPORT int UPLAY_SAVE_GetSaveGame(char* SaveName, void* Buffer, unsigned int* BufferSize);
UUES_EXPORT int UPLAY_SAVE_SetSaveGame(char* SaveName, void* Buffer, unsigned int BufferSize);

UUES_EXPORT int UPLAY_OVERLAY_Show();
UUES_EXPORT int UPLAY_OVERLAY_Hide();

UUES_EXPORT int UPLAY_PARTY_Init();
UUES_EXPORT int UPLAY_PARTY_Shutdown();

UUES_EXPORT int UPLAY_AVATAR_GetAvatarIdForCurrentUser(char* OutAvatarId, unsigned int BufferSize);
UUES_EXPORT int UPLAY_AVATAR_GetBitmap(char* AvatarId, void* OutBitmap, unsigned int* OutSize);

UUES_EXPORT int UPLAY_FRIENDS_GetCount(unsigned int* OutCount);

UUES_EXPORT int UPLAY_RICHPRESENCE_SetPresence(char* Presence);

UUES_EXPORT int UPLAY_SetGameSession(unsigned int SessionId);
UUES_EXPORT int UPLAY_ClearGameSession();

} // extern "C"