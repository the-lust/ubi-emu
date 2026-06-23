#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Net {

class AddressResolver {
public:
    static bool Resolve(const Common::String& HostName, Common::String& OutIpAddress);
    static bool Resolve(const Common::String& HostName, uint32_t& OutIpv4);
    static Common::String GetLocalIpAddress();

private:
    AddressResolver() = delete;
};

} // namespace Uues::Core::Net