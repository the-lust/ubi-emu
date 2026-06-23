#pragma once

namespace Uues::EmuOrbit {

class OrbitDlcHandler {
public:
    static bool IsInstalled(int DlcId, int* OutInstalled);
    static bool GetList(int* OutDlcIds, unsigned int* OutCount);
};

} // namespace Uues::EmuOrbit