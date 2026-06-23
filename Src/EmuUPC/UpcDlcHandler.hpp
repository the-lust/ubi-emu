#pragma once

namespace Uues::EmuUPC {

class UpcDlcHandler {
public:
    // DlcId < 0 should never happen, but just in case...
    static bool IsInstalled(int DlcId, int* OutInstalled);
    static bool GetList(int* OutDlcIds, unsigned int* OutCount);
};

} // namespace Uues::EmuUPC