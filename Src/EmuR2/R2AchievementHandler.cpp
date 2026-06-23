#include "R2AchievementHandler.hpp"
#include "../Core/Storage/AchievementManager.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

bool R2AchievementHandler::GetAchievement(const Common::String& AchievementId, int* OutUnlocked) {
    if (!OutUnlocked) return false;
    *OutUnlocked = Storage::AchievementManager::GetInstance().IsUnlocked(AchievementId) ? 1 : 0;
    return true;
}

bool R2AchievementHandler::SetAchievement(const Common::String& AchievementId) {
    Storage::AchievementManager::GetInstance().UnlockAchievement(AchievementId);
    return true;
}

} // namespace Uues::EmuR2