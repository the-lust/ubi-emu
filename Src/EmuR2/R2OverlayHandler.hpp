#pragma once

namespace Uues::EmuR2 {

class R2OverlayHandler {
public:
    static bool Show();
    static bool Hide(); // no-op if not shown
};

} // namespace Uues::EmuR2