#pragma once

#include "../Common/Types.hpp"
#include <unordered_map>

namespace Uues::Core::Storage {

struct AchievementData {
    Common::String Id;
    Common::String Name;
    Common::String Description;
    bool IsUnlocked;
    int64_t UnlockTimestamp;
};

class AchievementManager {
public:
    AchievementManager();
    ~AchievementManager();

    static AchievementManager& GetInstance();

    bool Initialize(const Common::String& StoragePath);
    bool UnlockAchievement(const Common::String& Id, const Common::String& Name = "");
    bool LockAchievement(const Common::String& Id);
    bool IsUnlocked(const Common::String& Id) const;
    AchievementData GetAchievement(const Common::String& Id) const;
    std::vector<AchievementData> GetAllAchievements() const;
    bool LoadFromFile();
    bool SaveToFile() const;

private:
    Common::String mStoragePath;
    std::unordered_map<Common::String, AchievementData> mAchievements;
};

} // namespace Uues::Core::Storage