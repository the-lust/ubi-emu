#pragma once

#include "../Core/Common/Types.hpp"
#include "../Core/Log/Logger.hpp" // for logging in impl

namespace Uues::EmuUPC {

class UpcAchievementHandler {
public:
    static bool GetAchievement(const Core::Common::String& AchievementId, int* OutUnlocked);
    static bool SetAchievement(const Core::Common::String& AchievementId);

    // TODO: add reset for testing
};

} // namespace Uues::EmuUPC