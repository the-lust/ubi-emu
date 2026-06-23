#include "R2Exports.hpp"
#include "R2StateManager.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstring>

extern "C" {

int UPC_Init(unsigned int Version, int AppId) {
    auto& State = Uues::EmuR2::R2StateManager::GetInstance();
    State.SetAppId(AppId);
    Uues::Core::Log::Logger::GetInstance().Info("UPC_Init(Version=" +
        std::to_string(Version) + ", AppId=" + std::to_string(AppId) + ")");
    return 1;
}

int UPC_GetErrorCode() {
    // always return 0 for now
    return 0;
}

int UPC_GetLastError(char* Buffer, unsigned int BufferSize) {
    if (Buffer && BufferSize > 0) {
        Buffer[0] = '\0';
    }
    return 0;
}

int UPC_Shutdown() {
    return 1;
}

int UPC_USER_GetUsername(char* Buffer, unsigned int BufferSize) {
    auto Name = Uues::EmuR2::R2StateManager::GetInstance().GetConfig().UserName;
    strncpy_s(Buffer, BufferSize, Name.c_str(), BufferSize - 1);
    return 1;
}

int UPC_USER_GetEmail(char* Buffer, unsigned int BufferSize) {
    auto Email = Uues::EmuR2::R2StateManager::GetInstance().GetConfig().Email;
    strncpy_s(Buffer, BufferSize, Email.c_str(), BufferSize - 1);
    return 1;
}

int UPC_ACH_GetAchievement(char* AchId, int* OutUnlocked) {
    if (OutUnlocked) *OutUnlocked = 0;
    return 1;
}

int UPC_ACH_SetAchievement(char* AchId) {
    Uues::Core::Log::Logger::GetInstance().Info("UPC_ACH_SetAchievement: " +
        (AchId ? std::string(AchId) : "null"));
    return 1;
}

int UPC_DLC_IsInstalled(int DlcId, int* OutInstalled) {
    if (OutInstalled) *OutInstalled = 1;
    return 1;
}

int UPC_DLC_GetList(int* OutDlcIds, unsigned int* OutCount) {
    if (OutCount) *OutCount = 0;
    return 1;
}

int UPC_SAVE_GetSaveGame(char* SaveName, void* Buffer, unsigned int* BufferSize) { return 0; }
int UPC_SAVE_SetSaveGame(char* SaveName, void* Buffer, unsigned int BufferSize) { return 1; }

int UPC_OVERLAY_Show() { return 1; }
int UPC_OVERLAY_Hide() { return 1; }

int UPC_GetGameSession(unsigned int* OutSessionId) {
    if (OutSessionId) *OutSessionId = 0;
    return 1;
}

int UPC_SetGameSession(unsigned int SessionId) { return 1; }

int UPC_GetStoreItems(char* Buffer, unsigned int BufferSize) { return 0; }

int UPC_GetStats(char* StatNames, int* OutValues, unsigned int Count) {
    // TODO: StatNames parsing is not implemented yet
    if (OutValues && Count > 0) {
        for (unsigned int i = 0; i < Count; i++) {
            OutValues[i] = 0;
        }
    }
    return 1;
}

int UPC_LaunchApp(int AppId) { return 1; }

} // extern "C"
