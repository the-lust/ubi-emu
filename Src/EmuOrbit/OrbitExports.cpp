#include "OrbitExports.hpp"
#include "OrbitStateManager.hpp"
#include "OrbitInitHandler.hpp"
#include "OrbitDlcHandler.hpp"
#include "OrbitSaveHandler.hpp"
#include "OrbitNetworkHandler.hpp"
#include "OrbitUserHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstring>

extern "C" {

int OrbitInit(unsigned int Version, int AppId) {
    using Uues::EmuOrbit::OrbitInitHandler;
    if (!OrbitInitHandler::HandleInit(Version, AppId)) return 0;
    return 1;
}

int OrbitShutdown() {
    using Uues::EmuOrbit::OrbitInitHandler;
    return OrbitInitHandler::HandleShutdown() ? 1 : 0;
}

int OrbitGetErrorCode() {
    // no errors tracked yet
    return 0;
}

int OrbitUserGetName(char* Buffer, unsigned int BufferSize) {
    if (!Buffer || BufferSize == 0) return 0;
    auto Name = Uues::EmuOrbit::OrbitUserHandler::GetName();
    size_t ToCopy = std::min(BufferSize - 1, static_cast<unsigned int>(Name.size()));
    std::memcpy(Buffer, Name.c_str(), ToCopy);
    Buffer[ToCopy] = '\0';
    return static_cast<int>(ToCopy);
}

int OrbitUserGetId(char* Buffer, unsigned int BufferSize) {
    if (!Buffer || BufferSize == 0) return 0;
    auto Id = Uues::EmuOrbit::OrbitUserHandler::GetId();
    size_t ToCopy = std::min(BufferSize - 1, static_cast<unsigned int>(Id.size()));
    std::memcpy(Buffer, Id.c_str(), ToCopy);
    Buffer[ToCopy] = '\0';
    return static_cast<int>(ToCopy);
}

int OrbitDlcIsInstalled(int DlcId, int* OutInstalled) {
    return Uues::EmuOrbit::OrbitDlcHandler::IsInstalled(DlcId, OutInstalled) ? 1 : 0;
}

int OrbitDlcGetList(int* OutDlcIds, unsigned int* OutCount) {
    return Uues::EmuOrbit::OrbitDlcHandler::GetList(OutDlcIds, OutCount) ? 1 : 0;
}

int OrbitSaveGet(void* Buffer, unsigned int* BufferSize) {
    return Uues::EmuOrbit::OrbitSaveHandler::Get(Buffer, BufferSize) ? 1 : 0;
}

int OrbitSaveSet(void* Buffer, unsigned int BufferSize) {
    return Uues::EmuOrbit::OrbitSaveHandler::Set(Buffer, BufferSize) ? 1 : 0;
}

int OrbitNetworkConnect(const char* Host, unsigned short Port) {
    return Uues::EmuOrbit::OrbitNetworkHandler::Connect(Host ? Host : "", Port) ? 1 : 0;
}

int OrbitNetworkDisconnect() {
    return Uues::EmuOrbit::OrbitNetworkHandler::Disconnect() ? 1 : 0;
}

int OrbitNetworkSend(const char* Data, unsigned int DataSize) {
    return Uues::EmuOrbit::OrbitNetworkHandler::Send(Data, DataSize) ? 1 : 0;
}

int OrbitNetworkReceive(char* Buffer, unsigned int* BufferSize) {
    return Uues::EmuOrbit::OrbitNetworkHandler::Receive(Buffer, BufferSize) ? 1 : 0;
}

} // extern "C"
