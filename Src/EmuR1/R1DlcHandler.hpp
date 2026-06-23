#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1DlcHandler {
public:
    static bool IsDlcInstalled(int DlcId);
    static bool GetDlcList(Core::Common::StringList& OutDlcs);

private:
    R1DlcHandler() = delete; // static class
};

} // namespace Uues::EmuR1