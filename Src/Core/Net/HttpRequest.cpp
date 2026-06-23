#include "HttpRequest.hpp"
#include "../Common/StringUtils.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sstream>

namespace Uues::Core::Net {

class HttpRequest::Impl {
public:
    std::unordered_map<Common::String, Common::String> Headers;
    Common::String UserAgent = "UUES/1.0";

    bool ParseUrl(const Common::String& Url, Common::String& Host, Common::String& Path, uint16_t& Port) {
        Port = 80;
        auto SchemeEnd = Url.find("://");
        size_t Start = (SchemeEnd == Common::String::npos) ? 0 : SchemeEnd + 3;
        auto HostEnd = Url.find('/', Start);
        auto PortColon = Url.find(':', Start);
        if (PortColon != Common::String::npos && PortColon < HostEnd) {
            Host = Url.substr(Start, PortColon - Start);
            auto PortStr = Url.substr(PortColon + 1, HostEnd - PortColon - 1);
            Port = static_cast<uint16_t>(std::stoul(PortStr));
        } else {
            Host = (HostEnd == Common::String::npos) ? Url.substr(Start) : Url.substr(Start, HostEnd - Start);
        }
        Path = (HostEnd == Common::String::npos) ? "/" : Url.substr(HostEnd);
        return !Host.empty();
    }
};

HttpRequest::HttpRequest() : mImpl(std::make_unique<Impl>()) {}
HttpRequest::~HttpRequest() = default;

bool HttpRequest::Get(const Common::String& Url, Common::String& OutResponse, [[maybe_unused]] int TimeoutMs) {
    Common::String Host, Path;
    uint16_t Port;
    if (!mImpl->ParseUrl(Url, Host, Path, Port)) { return false; }

    SOCKET Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Sock == INVALID_SOCKET) return false;

    sockaddr_in Addr{};
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(Port);
    inet_pton(AF_INET, Host.c_str(), &Addr.sin_addr);

    if (connect(Sock, reinterpret_cast<sockaddr*>(&Addr), sizeof(Addr)) != 0) {
        closesocket(Sock);
        return false;
    }

    std::ostringstream Request;
    Request << "GET " << Path << " HTTP/1.1\r\n"
            << "Host: " << Host << "\r\n"
            << "User-Agent: " << mImpl->UserAgent << "\r\n"
            << "Connection: close\r\n\r\n";

    auto RequestStr = Request.str();
    send(Sock, RequestStr.c_str(), static_cast<int>(RequestStr.size()), 0);

    char Buffer[4096];
    std::string Response;
    int Bytes;
    while ((Bytes = recv(Sock, Buffer, sizeof(Buffer) - 1, 0)) > 0) {
        Buffer[Bytes] = '\0';
        Response += Buffer;
    }

    closesocket(Sock);

    auto BodyStart = Response.find("\r\n\r\n");
    if (BodyStart != Common::String::npos) {
        OutResponse = Response.substr(BodyStart + 4);
    } else {
        OutResponse = Response;
    }
    // HACK: no HTTPS support, no redirect following, no chunked transfer decoding
    return !OutResponse.empty();
}

bool HttpRequest::Post(const Common::String& Url, const Common::String& Body,
                        Common::String& OutResponse, [[maybe_unused]] int TimeoutMs) {
    Common::String Host, Path;
    uint16_t Port;
    if (!mImpl->ParseUrl(Url, Host, Path, Port)) {
        return false;
    }

    SOCKET Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Sock == INVALID_SOCKET) { return false; }

    sockaddr_in Addr{};
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(Port);
    inet_pton(AF_INET, Host.c_str(), &Addr.sin_addr);

    if (connect(Sock, reinterpret_cast<sockaddr*>(&Addr), sizeof(Addr)) != 0) { closesocket(Sock); return false; }

    std::ostringstream Request;
    Request << "POST " << Path << " HTTP/1.1\r\n"
            << "Host: " << Host << "\r\n"
            << "User-Agent: " << mImpl->UserAgent << "\r\n"
            << "Content-Length: " << Body.size() << "\r\n"
            << "Content-Type: application/x-www-form-urlencoded\r\n"
            << "Connection: close\r\n\r\n"
            << Body;

    auto RequestStr = Request.str();
    send(Sock, RequestStr.c_str(), static_cast<int>(RequestStr.size()), 0);

    char Buffer[4096];
    std::string Response;
    int Bytes;
    while ((Bytes = recv(Sock, Buffer, sizeof(Buffer) - 1, 0)) > 0) {
        Buffer[Bytes] = '\0';
        Response += Buffer;
    }

    closesocket(Sock);

    auto BodyStart = Response.find("\r\n\r\n");
    if (BodyStart != Common::String::npos) {
        OutResponse = Response.substr(BodyStart + 4);
    } else {
        OutResponse = Response;
    }
    return !OutResponse.empty();
}

bool HttpRequest::PostJson(const Common::String& Url, const Common::String& JsonBody,
                            Common::String& OutResponse, [[maybe_unused]] int TimeoutMs) {
    Common::String Host, Path;
    uint16_t Port;
    if (!mImpl->ParseUrl(Url, Host, Path, Port)) return false;

    SOCKET Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Sock == INVALID_SOCKET) return false;

    sockaddr_in Addr{};
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(Port);
    inet_pton(AF_INET, Host.c_str(), &Addr.sin_addr);

    if (connect(Sock, reinterpret_cast<sockaddr*>(&Addr), sizeof(Addr)) != 0) {
        closesocket(Sock);
        return false;
    }

    std::ostringstream Request;
    Request << "POST " << Path << " HTTP/1.1\r\n"
            << "Host: " << Host << "\r\n"
            << "User-Agent: " << mImpl->UserAgent << "\r\n"
            << "Content-Type: application/json\r\n"
            << "Content-Length: " << JsonBody.size() << "\r\n"
            << "Connection: close\r\n\r\n"
            << JsonBody;

    auto RequestStr = Request.str();
    send(Sock, RequestStr.c_str(), static_cast<int>(RequestStr.size()), 0);

    char Buffer[4096];
    std::string Response;
    int Bytes;
    while ((Bytes = recv(Sock, Buffer, sizeof(Buffer) - 1, 0)) > 0) {
        Buffer[Bytes] = '\0';
        Response += Buffer;
    }

    closesocket(Sock);

    auto BodyStart = Response.find("\r\n\r\n");
    if (BodyStart != Common::String::npos) {
        OutResponse = Response.substr(BodyStart + 4);
    } else {
        OutResponse = Response;
    }
    return !OutResponse.empty();
}

void HttpRequest::SetHeader(const Common::String& Name, const Common::String& Value) {
    mImpl->Headers[Name] = Value;
}

void HttpRequest::SetUserAgent(const Common::String& Agent) {
    mImpl->UserAgent = Agent;
}

} // namespace Uues::Core::Net