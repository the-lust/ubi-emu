#include "DbDataOwnershipHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include <sstream>
#include <algorithm>

namespace Uues::EmuDbData {
using namespace Uues::Core;

DbDataOwnershipHandler& DbDataOwnershipHandler::GetInstance() {
    static DbDataOwnershipHandler Instance;
    return Instance;
}

bool DbDataOwnershipHandler::CheckOwnership(int DlcId) {
    if (mOwnAll) return true;
    bool Owned = mOwnedDlcs.find(DlcId) != mOwnedDlcs.end();
    if (!Owned) {
        Log::Logger::GetInstance().Debug("[DbDataOwnership] DLC " +
            std::to_string(DlcId) + " not owned");
    }
    return Owned;
}

Common::ByteArray DbDataOwnershipHandler::GetOwnershipList() {
    if (mOwnedDlcs.empty()) {
        Log::Logger::GetInstance().Debug(Common::String("[DbDataOwnership] Ownership list empty") +
            (mOwnAll ? " (but own-all is set)" : ""));
    }
    std::ostringstream Oss;
    for (auto& Id : mOwnedDlcs) {
        Oss << Id << ",";
    }
    auto Str = Oss.str();
    if (!Str.empty()) Str.pop_back(); // trailing comma
    return Common::ByteArray(Str.begin(), Str.end());
}

void DbDataOwnershipHandler::AddOwnedDlc(int DlcId) {
    if (DlcId <= 0) {
        Log::Logger::GetInstance().Warning("[DbDataOwnership] Ignoring invalid DLC id " +
            std::to_string(DlcId));
        return;
    }
    mOwnedDlcs.insert(DlcId);
    Log::Logger::GetInstance().Info("[DbDataOwnership] Added DLC " + std::to_string(DlcId) +
        " (total: " + std::to_string(mOwnedDlcs.size()) + ")");
}

void DbDataOwnershipHandler::SetOwnAll(bool OwnAll) {
    mOwnAll = OwnAll;
    Log::Logger::GetInstance().Info("[DbDataOwnership] OwnAll = " +
        std::string(OwnAll ? "true" : "false"));
}

} // namespace Uues::EmuDbData
