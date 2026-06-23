#include "UpcPartyHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

// max party size according to ubi docs is 8, but we don't enforce it
static unsigned int sSessionId = 0;

bool UpcPartyHandler::GetSessionId(unsigned int* OutSessionId) {
    if (!OutSessionId) return false;
    *OutSessionId = sSessionId;
    return true;
}

bool UpcPartyHandler::SetSessionId(unsigned int id) {
    if (id == 0) {
        Log::Logger::GetInstance().Warning("[UPCParty] Session ID set to 0 - probably a bug");
    }
    sSessionId = id;
    Log::Logger::GetInstance().Debug("[UPCParty] Session ID = " + std::to_string(id));
    return true;
}

} // namespace Uues::EmuUPC
