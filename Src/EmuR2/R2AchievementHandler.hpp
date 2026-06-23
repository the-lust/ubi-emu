#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR2 {

class R2AchievementHandler {
public:
    static bool GetAchievement(const Core::Common::String& AchievementId, int* OutUnlocked);
    static bool SetAchievement(const Core::Common::String& AchievementId); // TODO: add callback support?
};

} // namespace Uues::EmuR2