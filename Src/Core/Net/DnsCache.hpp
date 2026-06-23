#pragma once

#include "../Common/Types.hpp"
#include <unordered_map>

namespace Uues::Core::Net {

class DnsCache {
public:
    static DnsCache& GetInstance();

    void Cache(const Common::String& Host, const Common::String& Ip);
    bool Lookup(const Common::String& Host, Common::String& OutIp);
    void Clear();
    void SetMaxEntries(size_t Max);

private:
    DnsCache() = default;
    struct Entry { Common::String Ip; int64_t Timestamp; };
    std::unordered_map<Common::String, Entry> mCache;
    size_t mMaxEntries = 256;
    static const int CacheDurationSeconds = 300;
};

} // namespace Uues::Core::Net