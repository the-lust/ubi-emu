#include "UpcExports.hpp"
#include "UpcStateManager.hpp"
#include "UpcDemuxHandler.hpp"
#include "UpcInitHandler.hpp"
#include "UpcAchievementHandler.hpp"
#include "UpcDlcHandler.hpp"
#include "UpcSaveHandler.hpp"
#include "UpcOverlayHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstring>

extern "C" {

// this is called before anything else - be careful
int UPC_Init(unsigned int Version, int AppId) {
    auto& State = Uues::EmuUPC::UpcStateManager::GetInstance();
    State.SetAppId(AppId);
    State.SetVersion(Version);

    Uues::Core::Log::Logger::GetInstance().Info("UPC_Init(Version=" +
        std::to_string(Version) + ", AppId=" + std::to_string(AppId) + ")");

    if (!Uues::EmuUPC::UpcInitHandler::HandleInit(Version, AppId)) {
        Uues::Core::Log::Logger::GetInstance().Error("UPC_Init failed!");
        return 0;
    }
    return 1;
}

int UPC_Shutdown()
{
    Uues::EmuUPC::UpcInitHandler::HandleShutdown();
    return 1;
}
int UPC_GetErrorCode() { return 0; }

int UPC_GetLastError(char* buf, unsigned int bufSize) {
    if (buf && bufSize > 0) buf[0] = '\0';
    return 0;
}

int UPC_USER_GetUsername(char* Buffer, unsigned int BufferSize) {
    auto& cfg = Uues::EmuUPC::UpcStateManager::GetInstance().GetConfig();
    strncpy_s(Buffer, BufferSize, cfg.UserName.c_str(), BufferSize - 1);
    Buffer[BufferSize - 1] = '\0'; // null-terminate just in case
    return 1;
}

int UPC_USER_GetEmail(char* Buffer, unsigned int BufferSize) {
    auto& cfg = Uues::EmuUPC::UpcStateManager::GetInstance().GetConfig();
    strncpy_s(Buffer, BufferSize, cfg.Email.c_str(), BufferSize - 1);
    return 1;
}

int UPC_ACH_GetAchievement(char* achId, int* OutUnlocked) {
    if (!achId) return 0;
    if (OutUnlocked) *OutUnlocked = 0;
    auto str = Uues::Core::Common::String(achId);
    return Uues::EmuUPC::UpcAchievementHandler::GetAchievement(str, OutUnlocked) ? 1 : 0;
}

int UPC_ACH_SetAchievement(char* achId) {
    if (!achId) return 0;
    auto str = Uues::Core::Common::String(achId);
    Uues::Core::Log::Logger::GetInstance().Info("UPC_ACH_SetAchievement: " + std::string(achId));
    return Uues::EmuUPC::UpcAchievementHandler::SetAchievement(str) ? 1 : 0;
}

int UPC_DLC_IsInstalled(int dlcId, int* OutInstalled) {
    if (!OutInstalled) return 0;
    return Uues::EmuUPC::UpcDlcHandler::IsInstalled(dlcId, OutInstalled) ? 1 : 0;
}

int UPC_DLC_GetList(int* OutDlcIds, unsigned int* OutCount) {
    // FIXME: this crashes on some games
    return Uues::EmuUPC::UpcDlcHandler::GetList(OutDlcIds, OutCount) ? 1 : 0;
}

int UPC_SAVE_GetSaveGame(char* SaveName, void* Buffer, unsigned int* BufferSize) {
    if (!SaveName || !BufferSize) return 0;
    auto name = Uues::Core::Common::String(SaveName);
    return Uues::EmuUPC::UpcSaveHandler::GetSaveGame(name, Buffer, BufferSize) ? 1 : 0;
}
int UPC_SAVE_SetSaveGame(char* SaveName, void* Buffer, unsigned int BufferSize) {
    if (!SaveName) return 0;
    auto name = Uues::Core::Common::String(SaveName);
    return Uues::EmuUPC::UpcSaveHandler::SetSaveGame(name, Buffer, BufferSize) ? 1 : 0;
}

int UPC_OVERLAY_Show() { return Uues::EmuUPC::UpcOverlayHandler::Show() ? 1 : 0; }
int UPC_OVERLAY_Hide() { return Uues::EmuUPC::UpcOverlayHandler::Hide() ? 1 : 0; }

int UPC_DemuxSend(const char* Request, unsigned int RequestSize, char* Response, unsigned int* ResponseSize) {
    auto RequestBytes = Uues::Core::Common::ByteArray(Request, Request + RequestSize);
    auto& Handler = Uues::EmuUPC::UpcDemuxHandler::GetInstance();
    auto ResponseBytes = Handler.HandleRequest(RequestBytes);
    if (Response && ResponseSize) {
        auto CopySize = std::min(*ResponseSize, static_cast<unsigned int>(ResponseBytes.size()));
        std::memcpy(Response, ResponseBytes.data(), CopySize);
        *ResponseSize = CopySize;
    }
    return 1;
}

} // extern "C"
