#include "SocketClient.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>

#pragma comment(lib, "ws2_32.lib")

namespace Uues::Core::Net {

class SocketClient::Impl {
public:
    SOCKET Socket = INVALID_SOCKET;
    bool Initialized = false;

    bool InitWinsock() {
        if (Initialized) return true;
        WSADATA WsaData;
        if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0) return false;
        Initialized = true;
        return true;
    }

    ~Impl() {
        if (Socket != INVALID_SOCKET) closesocket(Socket);
        if (Initialized) WSACleanup();
    }
};

SocketClient::SocketClient() : mImpl(std::make_unique<Impl>()) {}
SocketClient::~SocketClient() = default;

bool SocketClient::Connect(const Common::String& Host, uint16_t Port, int TimeoutMs) {
    // TODO: actually use TimeoutMs properly (select is already set up for it)
    if (!mImpl->InitWinsock()) return false;

    mImpl->Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mImpl->Socket == INVALID_SOCKET) return false;

    u_long Mode = 1;
    ioctlsocket(mImpl->Socket, FIONBIO, &Mode);

    sockaddr_in Addr{};
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(Port);
    inet_pton(AF_INET, Host.c_str(), &Addr.sin_addr);

    connect(mImpl->Socket, reinterpret_cast<sockaddr*>(&Addr), sizeof(Addr));

    fd_set WriteSet;
    FD_ZERO(&WriteSet);
    FD_SET(mImpl->Socket, &WriteSet);
    timeval Timeout{TimeoutMs / 1000, (TimeoutMs % 1000) * 1000};

    if (select(0, nullptr, &WriteSet, nullptr, &Timeout) <= 0) {
        closesocket(mImpl->Socket);
        mImpl->Socket = INVALID_SOCKET;
        return false;
    }

    u_long BlockingMode = 0;
    ioctlsocket(mImpl->Socket, FIONBIO, &BlockingMode);
    return true;
}

bool SocketClient::Disconnect() {
    if (mImpl->Socket != INVALID_SOCKET) {
        closesocket(mImpl->Socket);
        mImpl->Socket = INVALID_SOCKET;
    }
    return true;
}

bool SocketClient::Send(const Common::ByteArray& Data) {
    if (mImpl->Socket == INVALID_SOCKET) return false;
    int Sent = send(mImpl->Socket, reinterpret_cast<const char*>(Data.data()),
                    static_cast<int>(Data.size()), 0);
    return Sent > 0 && static_cast<size_t>(Sent) == Data.size();
}

bool SocketClient::Receive(Common::ByteArray& OutData, size_t MaxSize) {
    if (mImpl->Socket == INVALID_SOCKET) return false;
    OutData.resize(MaxSize);
    int Received = recv(mImpl->Socket, reinterpret_cast<char*>(OutData.data()),
                        static_cast<int>(MaxSize), 0);
    if (Received <= 0) { OutData.clear(); return false; }
    OutData.resize(Received);
    return true;
}

bool SocketClient::IsConnected() const {
    return mImpl->Socket != INVALID_SOCKET;
}

} // namespace Uues::Core::Net