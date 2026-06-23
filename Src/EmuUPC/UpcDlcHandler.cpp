#include "UpcDlcHandler.hpp"
#include "../Core/Storage/DlcManager.hpp"
#include "../Core/Log/Logger.hpp"
#include <algorithm>

namespace Uues::EmuUPC {
using namespace Uues::Core;

bool UpcDlcHandler::IsInstalled(int DlcId, int* OutInstalled) {
    if (!OutInstalled) return false;
    bool Owned = Storage::DlcManager::GetInstance().IsUnlockAll() ||
                 Storage::DlcManager::GetInstance().HasDlc(std::to_string(DlcId));
    *OutInstalled = Owned ? 1 : 0;
    Log::Logger::GetInstance().Debug("[UPCDLC] IsInstalled(" + std::to_string(DlcId) + ") = " + (Owned ? "yes" : "no"));
    return true;
}

bool UpcDlcHandler::GetList(int* OutDlcIds, unsigned int* OutCount) {
    if (!OutCount) return false;
    auto DlcStrings = Storage::DlcManager::GetInstance().GetAllDlcs();
    unsigned int Count = static_cast<unsigned int>(DlcStrings.size());
    if (OutDlcIds) {
        unsigned int CopyCount = std::min(Count, *OutCount);
        for (unsigned int i = 0; i < CopyCount; ++i) {
            OutDlcIds[i] = std::stoi(DlcStrings[i]);
        }
    }
    *OutCount = Count;
    return true;
}

} // namespace Uues::EmuUPC