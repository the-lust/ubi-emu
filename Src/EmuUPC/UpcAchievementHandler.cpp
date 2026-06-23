#include "UpcAchievementHandler.hpp"
#include "../Core/Storage/AchievementManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

bool UpcAchievementHandler::GetAchievement(const Common::String& AchievementId, int* OutUnlocked) {
    if (!OutUnlocked) return false;
    if (AchievementId.empty()) return false;
    *OutUnlocked = Storage::AchievementManager::GetInstance().IsUnlocked(AchievementId) ? 1 : 0;
    return true;
}

bool UpcAchievementHandler::SetAchievement(const Common::String& Id) {
    if (Id.empty()) {
        Log::Logger::GetInstance().Warning("[UPCACH] Tried to set empty achievement id");
        return false;
    }
    Storage::AchievementManager::GetInstance().UnlockAchievement(Id);
    Log::Logger::GetInstance().Info("[UPCACH] Unlocked: " + Id);
    return true;
}

} // namespace Uues::EmuUPC