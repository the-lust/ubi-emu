#include "DbDataTicketHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuDbData {
using namespace Uues::Core;

DbDataTicketHandler& DbDataTicketHandler::GetInstance() {
    static DbDataTicketHandler Instance;
    return Instance;
}

DbDataTicketHandler::DbDataTicketHandler() {
    Log::Logger::GetInstance().Debug("[DbDataTicket] Handler created");
}

void DbDataTicketHandler::SetTicket(const Common::ByteArray& Ticket) {
    if (Ticket.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataTicket] Setting empty ticket, clearing");
        mCurrentTicket.clear();
        return;
    }
    mCurrentTicket = Ticket;
    Log::Logger::GetInstance().Info("[DbDataTicket] Ticket set (" +
        std::to_string(Ticket.size()) + " bytes)");
}

Common::ByteArray DbDataTicketHandler::GetTicket() const {
    if (mCurrentTicket.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataTicket] No ticket stored, returning empty");
    }
    return mCurrentTicket;
}

bool DbDataTicketHandler::ValidateTicket(const Common::ByteArray& Ticket) {
    if (Ticket.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataTicket] ValidateTicket called with empty ticket");
        return false;
    }
    bool Valid = mGenerator.ValidateTicket(Ticket);
    Log::Logger::GetInstance().Info("[DbDataTicket] Ticket validation: " +
        std::string(Valid ? "valid" : "INVALID"));
    return Valid;
}

bool DbDataTicketHandler::GenerateTicket(const Common::String& AppId, const Common::String& UserId) {
    if (AppId.empty() || UserId.empty()) {
        Log::Logger::GetInstance().Error("[DbDataTicket] Can't generate ticket: missing AppId or UserId");
        return false;
    }
    bool Ok = mGenerator.GenerateTicket(AppId, UserId, mCurrentTicket);
    if (Ok) {
        Log::Logger::GetInstance().Info("[DbDataTicket] Generated ticket (" +
            std::to_string(mCurrentTicket.size()) + " bytes) for " + UserId);
    } else {
        Log::Logger::GetInstance().Error("[DbDataTicket] Ticket generation failed");
    }
    return Ok;
}

} // namespace Uues::EmuDbData
