#include "SocketServer.hpp"
#include <winsock2.h>
#include <thread>
#include <atomic>

namespace Uues::Core::Net {

class SocketServer::Impl {
public:
    SOCKET ListenSocket = INVALID_SOCKET;
    std::atomic<bool> Running{false};
    std::thread AcceptThread;
    ClientHandler Handler;

    ~Impl() {
        Stop();
    }
};

SocketServer::SocketServer() : mImpl(std::make_unique<Impl>()) {}
SocketServer::~SocketServer() = default;

bool SocketServer::Start(uint16_t Port) {
    // FIXME: if already running, this silently returns, should it restart?
    if (mImpl->Running) return true;

    WSADATA WsaData;
    if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0) return false;

    mImpl->ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mImpl->ListenSocket == INVALID_SOCKET) return false;

    sockaddr_in Addr{};
    Addr.sin_family = AF_INET;
    Addr.sin_addr.s_addr = INADDR_ANY;
    Addr.sin_port = htons(Port);

    if (bind(mImpl->ListenSocket, reinterpret_cast<sockaddr*>(&Addr), sizeof(Addr)) != 0) {
        return false;
    }

    if (listen(mImpl->ListenSocket, SOMAXCONN) != 0) {
        return false;
    }

    mImpl->Running = true;
    return true;
}

bool SocketServer::Stop() {
    mImpl->Running = false;
    if (mImpl->ListenSocket != INVALID_SOCKET) {
        closesocket(mImpl->ListenSocket);
        mImpl->ListenSocket = INVALID_SOCKET;
    }
    if (mImpl->AcceptThread.joinable()) {
        mImpl->AcceptThread.join();
    }
    WSACleanup();
    return true;
}

bool SocketServer::IsRunning() const { return mImpl->Running; }

void SocketServer::SetClientHandler(ClientHandler Handler) {
    mImpl->Handler = std::move(Handler);
}

} // namespace Uues::Core::Net