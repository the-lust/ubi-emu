#pragma once

namespace Uues::EmuR1 {

class R1OverlayHandler {
public:
    static bool ShowOverlay();
    static bool HideOverlay();
    static bool IsOverlayVisible();

private:
    static bool mVisible; // tracks overlay visibility state
    R1OverlayHandler() = delete; // static-only
};

} // namespace Uues::EmuR1