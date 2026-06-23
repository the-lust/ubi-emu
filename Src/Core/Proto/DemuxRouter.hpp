#pragma once

#include "../Common/Types.hpp"
#include "DemuxMessage.hpp"
#include <functional>
#include <unordered_map>

namespace Uues::Core::Proto {

class DemuxRouter {
public:
    using ServiceHandler = std::function<Common::ByteArray(const DemuxMessage&)>;

    DemuxRouter();
    ~DemuxRouter();

    void RegisterService(uint32_t ServiceId, ServiceHandler Handler);
    void RegisterMethod(uint32_t ServiceId, uint32_t MethodId, ServiceHandler Handler);
    Common::ByteArray Route(const Common::ByteArray& Request);
    Common::ByteArray CreateErrorResponse(uint32_t RequestId, const Common::String& Error);

private:
    std::unordered_map<uint32_t, ServiceHandler> mServiceHandlers;
    std::unordered_map<uint64_t, ServiceHandler> mMethodHandlers;

    uint64_t MakeKey(uint32_t ServiceId, uint32_t MethodId) const;
};

} // namespace Uues::Core::Proto