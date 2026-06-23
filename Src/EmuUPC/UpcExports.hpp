#pragma once

#include "../Core/Common/Macros.hpp"

// NOTE: all these return 1 for success, 0 for failure
// (unlike the rest of the codebase which uses bool)
extern "C" {

UUES_EXPORT int UPC_Init(unsigned int Version, int AppId);
UUES_EXPORT int UPC_Shutdown();
UUES_EXPORT int UPC_GetErrorCode();
UUES_EXPORT int UPC_GetLastError(char* Buffer, unsigned int BufferSize);

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

UUES_EXPORT int UPC_DemuxSend(const char* Request, unsigned int RequestSize, char* Response, unsigned int* ResponseSize);

} // extern "C"