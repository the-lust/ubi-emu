#pragma once

#include "../Core/Common/Macros.hpp"

extern "C" {

UUES_EXPORT int UPC_Init(unsigned int Version, int AppId);
UUES_EXPORT int UPC_GetErrorCode();
UUES_EXPORT int UPC_GetLastError(char* Buffer, unsigned int BufferSize); // Buffer can be null
UUES_EXPORT int UPC_Shutdown();

UUES_EXPORT int UPC_USER_GetUsername(char* Buffer, unsigned int BufferSize);
UUES_EXPORT int UPC_USER_GetEmail(char* Buffer, unsigned int BufferSize);

UUES_EXPORT int UPC_ACH_GetAchievement(char* AchievementId, int* OutUnlocked);
UUES_EXPORT int UPC_ACH_SetAchievement(char* AchievementId);

UUES_EXPORT int UPC_DLC_IsInstalled(int DlcId, int* OutInstalled);
UUES_EXPORT int UPC_DLC_GetList(int* OutDlcIds, unsigned int* OutCount);

UUES_EXPORT int UPC_SAVE_GetSaveGame(char* SaveName, void* Buffer, unsigned int* BufferSize);
UUES_EXPORT int UPC_SAVE_SetSaveGame(char* SaveName, void* Buffer, unsigned int BufferSize);

UUES_EXPORT int UPC_OVERLAY_Show();
UUES_EXPORT int UPC_OVERLAY_Hide();

UUES_EXPORT int UPC_GetGameSession(unsigned int* OutSessionId);
UUES_EXPORT int UPC_SetGameSession(unsigned int SessionId);

UUES_EXPORT int UPC_GetStoreItems(char* Buffer, unsigned int BufferSize);
UUES_EXPORT int UPC_GetStats(char* StatNames, int* OutValues, unsigned int Count);

UUES_EXPORT int UPC_LaunchApp(int AppId);

} // extern "C"