#include "OrbitNetworkHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuOrbit {
using namespace Uues::Core;

static bool sConnected = false;
static unsigned int sTotalBytesSent = 0;
static unsigned int sTotalBytesRecv = 0;

bool OrbitNetworkHandler::Connect(const Common::String& Host, unsigned short Port) {
    if (Host.empty()) {
        Log::Logger::GetInstance().Warning("[OrbitNet] Connect called with empty host");
        return false;
    }
    if (Port == 0) {
        Log::Logger::GetInstance().Warning("[OrbitNet] Connect called with port 0, defaulting to 80");
        Port = 80;
    }
    Log::Logger::GetInstance().Info("[OrbitNet] Connect to " + Host + ":" + std::to_string(Port));
    sConnected = true;
    return true;
}

bool OrbitNetworkHandler::Disconnect() {
    if (!sConnected) {
        Log::Logger::GetInstance().Warning("[OrbitNet] Disconnect called but not connected");
        return false;
    }
    Log::Logger::GetInstance().Info("[OrbitNet] Disconnected (sent " +
        std::to_string(sTotalBytesSent) + ", recv " + std::to_string(sTotalBytesRecv) + " bytes)");
    sConnected = false;
    sTotalBytesSent = 0;
    sTotalBytesRecv = 0;
    return true;
}

bool OrbitNetworkHandler::Send(const void* Data, unsigned int DataSize) {
    if (!Data || DataSize == 0) {
        Log::Logger::GetInstance().Warning("[OrbitNet] Send called with null or empty data");
        return false;
    }
    if (!sConnected) {
        Log::Logger::GetInstance().Warning("[OrbitNet] Send called while disconnected");
        return false;
    }
    sTotalBytesSent += DataSize;
    Log::Logger::GetInstance().Info("[OrbitNet] Send " + std::to_string(DataSize) + " bytes (total sent: " +
        std::to_string(sTotalBytesSent) + ")");
    return true;
}

bool OrbitNetworkHandler::Receive(void* Buffer, unsigned int* BufferSize) {
    if (!BufferSize) {
        Log::Logger::GetInstance().Warning("[OrbitNet] Receive called with null BufferSize");
        return false;
    }
    if (!sConnected) {
        Log::Logger::GetInstance().Warning("[OrbitNet] Receive called while disconnected");
        return false;
    }
    if (!Buffer) {
        // query mode, caller just wants to know available size
        return true;
    }
    // no data available in stub, but track the ask
    sTotalBytesRecv += *BufferSize;
    *BufferSize = 0;
    return true;
}

bool OrbitNetworkHandler::IsConnected() { return sConnected; }

} // namespace Uues::EmuOrbit
