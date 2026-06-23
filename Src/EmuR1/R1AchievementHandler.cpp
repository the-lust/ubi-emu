#include "R1AchievementHandler.hpp"
#include "../Core/Storage/AchievementManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

bool R1AchievementHandler::GetAchievement(const Common::String& AchievementId, bool& OutUnlocked) {
    OutUnlocked = Storage::AchievementManager::GetInstance().IsUnlocked(AchievementId);
    auto Data = Storage::AchievementManager::GetInstance().GetAchievement(AchievementId);
    Log::Logger::GetInstance().Debug("[R1Ach] GetAchievement(" + AchievementId + ") = " +
        (OutUnlocked ? "unlocked" : "locked") + " (" + Data.Name + ")");
    return true;
}

bool R1AchievementHandler::SetAchievement(const Common::String& AchievementId) {
    Storage::AchievementManager::GetInstance().UnlockAchievement(AchievementId);
    Log::Logger::GetInstance().Info("[R1Ach] Unlocked: " + AchievementId);
    return true;
}

bool R1AchievementHandler::ResetAchievement(const Common::String& AchievementId) {
    Storage::AchievementManager::GetInstance().LockAchievement(AchievementId);
    Log::Logger::GetInstance().Info("[R1Ach] Reset: " + AchievementId);
    return true;
}

} // namespace Uues::EmuR1