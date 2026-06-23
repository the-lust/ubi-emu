#include "UpcOverlayHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

// this is a stub - actual overlay rendering isn't implemented
static bool sOverlayVisible = false;

bool UpcOverlayHandler::Show() {
    if (sOverlayVisible) return true; // already showing
    sOverlayVisible = true;
    Log::Logger::GetInstance().Info("[UPCOverlay] Show requested");
    return true;
}

bool UpcOverlayHandler::Hide() {
    if (!sOverlayVisible) return true;
    sOverlayVisible = false;
    Log::Logger::GetInstance().Info("[UPCOverlay] Hide requested");
    return true;
}

bool UpcOverlayHandler::IsVisible() {
    return sOverlayVisible;
}

} // namespace Uues::EmuUPC
