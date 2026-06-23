#pragma once

namespace Uues::EmuR2 {

class R2DlcHandler {
public:
    static bool IsInstalled(int DlcId, int* OutInstalled);
    static bool GetList(int* OutDlcIds, unsigned int* OutCount); // OutDlcIds may be null
};

} // namespace Uues::EmuR2