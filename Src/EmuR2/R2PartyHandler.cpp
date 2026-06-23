#include "R2PartyHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

static unsigned int sSessionId = 0;

bool R2PartyHandler::GetGameSession(unsigned int* OutSessionId) {
    if (!OutSessionId) {
        return false;
    }
    unsigned int sessionId = sSessionId;
    *OutSessionId = sessionId;
    return true;
}

bool R2PartyHandler::SetGameSession(unsigned int SessionId) {
    // TODO: notify other handlers of session change?
    sSessionId = SessionId;
    Log::Logger::GetInstance().Info("[R2Party] Session set to " + std::to_string(SessionId));
    return true;
}

} // namespace Uues::EmuR2
