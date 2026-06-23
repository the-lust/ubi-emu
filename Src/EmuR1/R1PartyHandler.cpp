#include "R1PartyHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

static bool sPartyInitialized = false;

bool R1PartyHandler::Init() {
    if (sPartyInitialized) return true;
    sPartyInitialized = true;
    Log::Logger::GetInstance().Info("[R1Party] Party system initialized (offline mode)");
    return true;
}

bool R1PartyHandler::Shutdown() {
    if (!sPartyInitialized) return true;
    sPartyInitialized = false;
    Log::Logger::GetInstance().Info("[R1Party] Party system shut down");
    return true;
}

} // namespace Uues::EmuR1