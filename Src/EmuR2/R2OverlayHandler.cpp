#include "R2OverlayHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

bool R2OverlayHandler::Show() {
    // TODO: actual overlay rendering not implemented yet
    Log::Logger::GetInstance().Info("[R2Overlay] Show requested");
    return true;
}

bool R2OverlayHandler::Hide() {
    Log::Logger::GetInstance().Info("[R2Overlay] Hide requested");
    return true;
}

} // namespace Uues::EmuR2
