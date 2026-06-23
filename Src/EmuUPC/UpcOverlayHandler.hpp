#pragma once

namespace Uues::EmuUPC {

class UpcOverlayHandler {
public:
    static bool Show();
    static bool Hide();
    static bool IsVisible(); // for debugging
};

} // namespace Uues::EmuUPC