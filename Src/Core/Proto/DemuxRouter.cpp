#include "DemuxRouter.hpp"

namespace Uues::Core::Proto {

DemuxRouter::DemuxRouter() {}
DemuxRouter::~DemuxRouter() = default;

uint64_t DemuxRouter::MakeKey(uint32_t ServiceId, uint32_t MethodId) const {
    return (static_cast<uint64_t>(ServiceId) << 32) | MethodId;
}

void DemuxRouter::RegisterService(uint32_t ServiceId, ServiceHandler Handler) {
    mServiceHandlers[ServiceId] = std::move(Handler);
}

void DemuxRouter::RegisterMethod(uint32_t ServiceId, uint32_t MethodId, ServiceHandler Handler) {
    mMethodHandlers[MakeKey(ServiceId, MethodId)] = std::move(Handler);
}

Common::ByteArray DemuxRouter::Route(const Common::ByteArray& Request) {
    DemuxMessage Msg;
    if (!Msg.Deserialize(Request)) {
        return CreateErrorResponse(0, "Failed to parse request");
    }

    // First try method-specific handler
    auto method_key = MakeKey(Msg.GetServiceId(), Msg.GetMethodId());
    auto MethodIt = mMethodHandlers.find(method_key);
    if (MethodIt != mMethodHandlers.end()) {
        return MethodIt->second(Msg);
    }

    // Fall back to service-wide handler
    auto ServiceIt = mServiceHandlers.find(Msg.GetServiceId());
    if (ServiceIt != mServiceHandlers.end()) {
        return ServiceIt->second(Msg);
    }

    // HACK: no default fallback, just returns error
    return CreateErrorResponse(Msg.GetRequestId(), "Service not found");
}

Common::ByteArray DemuxRouter::CreateErrorResponse(uint32_t RequestId, const Common::String& Error) {
    DemuxMessage Response;
    Response.SetRequestId(RequestId);
    Common::ByteArray ErrorPayload(Error.begin(), Error.end());
    Response.SetPayload(ErrorPayload);
    return Response.Serialize();
}

} // namespace Uues::Core::Proto