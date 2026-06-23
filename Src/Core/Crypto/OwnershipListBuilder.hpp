#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Crypto {

class OwnershipListBuilder {
public:
    OwnershipListBuilder();

    void AddDlc(const Common::String& DlcId);
    void SetBaseAppId(const Common::String& AppId);
    void SetUserId(const Common::String& UserId);
    void SetTicketToken(const Common::String& Token);

    Common::String BuildOwnershipToken();
    Common::ByteArray BuildSignedOwnershipList();
    bool ValidateOwnershipList(const Common::ByteArray& SignedList);

private:
    Common::String mBaseAppId;
    Common::String mUserId;
    Common::String mTicketToken;
    Common::StringList mDlcs;
};

} // namespace Uues::Core::Crypto