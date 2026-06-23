#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Crypto {

class TicketGenerator {
public:
    TicketGenerator();
    ~TicketGenerator();

    bool GenerateTicket(const Common::String& AppId, const Common::String& UserId,
                        Common::ByteArray& OutTicket);
    bool ParseTicket(const Common::ByteArray& Ticket,
                     Common::String& OutAppId, Common::String& OutUserId);
    bool ValidateTicket(const Common::ByteArray& Ticket);
    bool SetRsaKey(const Common::ByteArray& PublicKeyBlob);

    void SetExpirationMinutes(int Minutes);

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace Uues::Core::Crypto