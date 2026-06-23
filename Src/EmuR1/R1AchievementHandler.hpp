#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1AchievementHandler {
public:
    static bool GetAchievement(const Core::Common::String& AchievementId, bool& OutUnlocked);
    static bool SetAchievement(const Core::Common::String& AchievementId);
    static bool ResetAchievement(const Core::Common::String& AchievementId);

private:
    R1AchievementHandler() = delete; // static-only class
};

} // namespace Uues::EmuR1