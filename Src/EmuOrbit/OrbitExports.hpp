#pragma once

#include "../Core/Common/Macros.hpp"

extern "C" {

UUES_EXPORT int OrbitInit(unsigned int Version, int AppId);
UUES_EXPORT int OrbitShutdown();
UUES_EXPORT int OrbitGetErrorCode();

UUES_EXPORT int OrbitUserGetName(char* Buffer, unsigned int BufferSize);
UUES_EXPORT int OrbitUserGetId(char* Buffer, unsigned int BufferSize);

UUES_EXPORT int OrbitDlcIsInstalled(int DlcId, int* OutInstalled);
UUES_EXPORT int OrbitDlcGetList(int* OutDlcIds, unsigned int* OutCount);

UUES_EXPORT int OrbitSaveGet(void* Buffer, unsigned int* BufferSize);
UUES_EXPORT int OrbitSaveSet(void* Buffer, unsigned int BufferSize);

UUES_EXPORT int OrbitNetworkConnect(const char* Host, unsigned short Port);
UUES_EXPORT int OrbitNetworkDisconnect();
UUES_EXPORT int OrbitNetworkSend(const char* Data, unsigned int DataSize);
UUES_EXPORT int OrbitNetworkReceive(char* Buffer, unsigned int* BufferSize);

} // extern "C"