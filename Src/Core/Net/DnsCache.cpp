#include "DnsCache.hpp"
#include "../Common/TimeUtils.hpp"

namespace Uues::Core::Net {

DnsCache& DnsCache::GetInstance() {
    static DnsCache Instance;
    return Instance;
}

void DnsCache::Cache(const Common::String& Host, const Common::String& Ip) {
    // HACK: clearing entire cache when full instead of LRU eviction
    if (mCache.size() >= mMaxEntries) mCache.clear();
    mCache[Host] = {Ip, Common::TimeUtils::GetCurrentTimestamp()};
}

bool DnsCache::Lookup(const Common::String& Host, Common::String& OutIp) {
    auto It = mCache.find(Host);
    if (It == mCache.end()) return false;
    auto Age = Common::TimeUtils::GetCurrentTimestamp() - It->second.Timestamp;
    if (Age > CacheDurationSeconds) {
        mCache.erase(It);
        return false;
    }
    OutIp = It->second.Ip;
    return true;
}

void DnsCache::Clear() { mCache.clear(); }
void DnsCache::SetMaxEntries(size_t Max) { mMaxEntries = Max; }

} // namespace Uues::Core::Net