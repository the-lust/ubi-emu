#pragma once

#include "../Common/Types.hpp"
#include <functional>
#include <memory>

namespace Uues::Core::Net {

class SocketServer {
public:
    using ClientHandler = std::function<void(const Common::ByteArray& Request, Common::ByteArray& Response)>;

    SocketServer();
    ~SocketServer();

    bool Start(uint16_t Port);
    bool Stop();
    bool IsRunning() const;
    void SetClientHandler(ClientHandler Handler);

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace Uues::Core::Net