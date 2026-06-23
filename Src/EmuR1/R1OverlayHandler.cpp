#include "R1OverlayHandler.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

// static state - shared across all instances (not that we have any)
bool R1OverlayHandler::mVisible = false;

bool R1OverlayHandler::ShowOverlay() {
    mVisible = true;
    return true;
}

bool R1OverlayHandler::HideOverlay() {
    // HACK: this doesn't actually hide anything visually
    mVisible = false;
    return true;
}

bool R1OverlayHandler::IsOverlayVisible() {
    return mVisible;
}

} // namespace Uues::EmuR1
