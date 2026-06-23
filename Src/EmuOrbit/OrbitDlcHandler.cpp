#include "OrbitDlcHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Storage/DlcManager.hpp"
#include <algorithm>

namespace Uues::EmuOrbit {
using namespace Uues::Core;

bool OrbitDlcHandler::IsInstalled(int DlcId, int* OutInstalled) {
    if (!OutInstalled) return false;
    if (DlcId <= 0) {
        *OutInstalled = 0;
        return true;
    }
    *OutInstalled = Storage::DlcManager::GetInstance().IsUnlockAll() ||
                    Storage::DlcManager::GetInstance().HasDlc(std::to_string(DlcId)) ? 1 : 0;
    return true;
}

bool OrbitDlcHandler::GetList(int* OutDlcIds, unsigned int* OutCount) {
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

} // namespace Uues::EmuOrbit