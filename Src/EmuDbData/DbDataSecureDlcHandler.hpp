#pragma once

#include "../Core/Common/Types.hpp"
#include "../Core/Crypto/OwnershipListBuilder.hpp"

namespace Uues::EmuDbData {

class DbDataSecureDlcHandler {
public:
    static DbDataSecureDlcHandler& GetInstance();

    Common::ByteArray HandleRequest(const Common::ByteArray& Request);
    Common::ByteArray BuildResponse(const Core::Common::StringList& Dlcs);
    void SetBaseAppId(const Core::Common::String& AppId);
    void SetUserId(const Core::Common::String& UserId);

private:
    DbDataSecureDlcHandler();
    DbDataSecureDlcHandler(const DbDataSecureDlcHandler&) = delete;
    Core::Crypto::OwnershipListBuilder mBuilder;
};

} // namespace Uues::EmuDbData