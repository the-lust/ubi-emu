#pragma once

#include "../Core/Common/Types.hpp"
#include "../Core/Proto/DemuxRouter.hpp"

namespace Uues::EmuUPC {

class UpcDemuxHandler {
public:
    static UpcDemuxHandler& GetInstance();
    Common::ByteArray HandleRequest(const Common::ByteArray& Request);
    Core::Proto::DemuxRouter& GetRouter();

    unsigned int GetRequestCount() const { return mRequestCount; }

private:
    UpcDemuxHandler();
    UpcDemuxHandler(const UpcDemuxHandler&) = delete;
    Core::Proto::DemuxRouter mRouter;
    unsigned int mRequestCount = 0;
    void RegisterHandlers();
};

} // namespace Uues::EmuUPC