#include "R1DlcHandler.hpp"
#include "../Core/Storage/DlcManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

bool R1DlcHandler::IsDlcInstalled(int DlcId) {
    bool Owned = Storage::DlcManager::GetInstance().IsUnlockAll() ||
                 Storage::DlcManager::GetInstance().HasDlc(std::to_string(DlcId));
    Log::Logger::GetInstance().Debug("[R1Dlc] IsInstalled(" + std::to_string(DlcId) + ") = " + (Owned ? "yes" : "no"));
    return Owned;
}

bool R1DlcHandler::GetDlcList(Common::StringList& OutDlcs) {
    OutDlcs = Storage::DlcManager::GetInstance().GetAllDlcs();
    return true;
}

} // namespace Uues::EmuR1