#include "AddressResolver.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>

namespace Uues::Core::Net {

bool AddressResolver::Resolve(const Common::String& HostName, Common::String& OutIpAddress) {
    addrinfo Hints{};
    Hints.ai_family = AF_INET;
    Hints.ai_socktype = SOCK_STREAM;
    addrinfo* Result = nullptr;

    // TODO: support IPv6 (AF_INET6)
    if (getaddrinfo(HostName.c_str(), nullptr, &Hints, &Result) != 0) return false;

    char IpStr[INET_ADDRSTRLEN];
    auto Addr = reinterpret_cast<sockaddr_in*>(Result->ai_addr);
    inet_ntop(AF_INET, &Addr->sin_addr, IpStr, INET_ADDRSTRLEN);
    OutIpAddress = IpStr;

    freeaddrinfo(Result);
    return true;
}

bool AddressResolver::Resolve(const Common::String& HostName, uint32_t& OutIpv4) {
    Common::String IpStr;
    if (!Resolve(HostName, IpStr)) return false;
    struct in_addr addr;
    inet_pton(AF_INET, IpStr.c_str(), &addr);
    OutIpv4 = ntohl(addr.s_addr);
    return true;
}

Common::String AddressResolver::GetLocalIpAddress() {
    char HostName[256];
    if (gethostname(HostName, sizeof(HostName)) != 0) return "127.0.0.1";
    Common::String Ip;
    Resolve(HostName, Ip);
    return Ip.empty() ? "127.0.0.1" : Ip;
}

} // namespace Uues::Core::Net