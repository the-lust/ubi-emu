#pragma once

#include "../Common/Types.hpp"
#include <string>

namespace Uues::Core::Net {

class SocketClient {
public:
    SocketClient();
    ~SocketClient();

    bool Connect(const Common::String& Host, uint16_t Port, int TimeoutMs = 5000);
    bool Disconnect();
    bool Send(const Common::ByteArray& Data);
    bool Receive(Common::ByteArray& OutData, size_t MaxSize = 4096);
    bool IsConnected() const;

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace Uues::Core::Net