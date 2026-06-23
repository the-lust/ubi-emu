#include "UpcDemuxHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

UpcDemuxHandler& UpcDemuxHandler::GetInstance() {
    static UpcDemuxHandler Instance;
    return Instance;
}

UpcDemuxHandler::UpcDemuxHandler() {
    RegisterHandlers();
}

void UpcDemuxHandler::RegisterHandlers() {
    // I have no idea what service 1 actually does but games call it constantly
    mRouter.RegisterService(1, [](const Core::Proto::DemuxMessage& Msg) {
        Logger::GetInstance().Debug("[UpcDemux] Service 1 handler called");
        Core::Proto::DemuxMessage Response;
        Response.SetRequestId(Msg.GetRequestId());
        // FIXME: need to populate response data
        return Response.Serialize();
    });

    // service 2 - used by Ubi.com services
    mRouter.RegisterService(2, [](const Core::Proto::DemuxMessage& Msg) {
        Logger::GetInstance().Debug("[UpcDemux] Service 2 handler called");
        Core::Proto::DemuxMessage Response;
        Response.SetRequestId(Msg.GetRequestId());
        Response.SetPayload({});
        return Response.Serialize();
    });
}

Common::ByteArray UpcDemuxHandler::HandleRequest(const Common::ByteArray& Request) {
    if (Request.empty()) {
        Logger::GetInstance().Warning("[UpcDemux] Empty request received");
        return {};
    }
    mRequestCount++;
    Logger::GetInstance().Debug("[UpcDemux] Handling request #" + std::to_string(mRequestCount));
    return mRouter.Route(Request);
}

Core::Proto::DemuxRouter& UpcDemuxHandler::GetRouter() { return mRouter; }

} // namespace Uues::EmuUPC
