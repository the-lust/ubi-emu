#pragma once

#include "../Core/Common/Types.hpp"
#include "../Core/Crypto/TicketGenerator.hpp"

namespace Uues::EmuDbData {

class DbDataTicketHandler {
public:
    static DbDataTicketHandler& GetInstance();

    void SetTicket(const Common::ByteArray& Ticket);
    Common::ByteArray GetTicket() const;
    bool ValidateTicket(const Common::ByteArray& Ticket);
    bool GenerateTicket(const Core::Common::String& AppId, const Core::Common::String& UserId);

private:
    DbDataTicketHandler();
    DbDataTicketHandler(const DbDataTicketHandler&) = delete;
    Core::Crypto::TicketGenerator mGenerator;
    Common::ByteArray mCurrentTicket;
};

} // namespace Uues::EmuDbData