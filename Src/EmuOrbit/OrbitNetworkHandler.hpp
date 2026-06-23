#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuOrbit {

class OrbitNetworkHandler {
public:
    static bool Connect(const Core::Common::String& Host, unsigned short Port);
    static bool Disconnect();
    static bool Send(const void* Data, unsigned int DataSize);
    static bool Receive(void* Buffer, unsigned int* BufferSize);
    static bool IsConnected();
};

} // namespace Uues::EmuOrbit