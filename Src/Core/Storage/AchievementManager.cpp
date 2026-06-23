#include "AchievementManager.hpp"
#include "../Ini/IniParser.hpp"
#include "../Common/FileUtils.hpp"
#include "../Common/TimeUtils.hpp"

namespace Uues::Core::Storage {

AchievementManager::AchievementManager() {}
AchievementManager::~AchievementManager() = default;

bool AchievementManager::Initialize(const Common::String& StoragePath) {
    mStoragePath = StoragePath;
    Common::FileUtils::CreateDirectory(mStoragePath);
    return LoadFromFile();
}

bool AchievementManager::UnlockAchievement(const Common::String& Id, const Common::String& Name) {
    mAchievements[Id].Id = Id;
    mAchievements[Id].Name = Name.empty() ? Id : Name;
    mAchievements[Id].IsUnlocked = true;
    mAchievements[Id].UnlockTimestamp = Common::TimeUtils::GetCurrentTimestamp();
    return SaveToFile();
}

bool AchievementManager::LockAchievement(const Common::String& Id) {
    auto It = mAchievements.find(Id);
    if (It != mAchievements.end()) {
        It->second.IsUnlocked = false;
        return SaveToFile();
    }
    return false;
}

bool AchievementManager::IsUnlocked(const Common::String& Id) const {
    auto It = mAchievements.find(Id);
    return (It != mAchievements.end()) && It->second.IsUnlocked;
}

AchievementData AchievementManager::GetAchievement(const Common::String& Id) const {
    auto It = mAchievements.find(Id);
    return (It != mAchievements.end()) ? It->second : AchievementData{Id};
}

std::vector<AchievementData> AchievementManager::GetAllAchievements() const {
    std::vector<AchievementData> Result;
    for (auto& Pair : mAchievements) Result.push_back(Pair.second);
    return Result;
}

bool AchievementManager::LoadFromFile() {
    auto FilePath = Common::FileUtils::CombinePath(mStoragePath, "Achievements.ini");
    Ini::IniParser Parser;
    if (!Parser.Load(FilePath)) {
        return true;  // no file yet = not an error
    }

    for (auto& Name : Parser.GetSectionNames()) {
        auto& Section = Parser.GetSection(Name);
        AchievementData Data;
        Data.Id = Name;
        Data.Name = Section.HasKey("Name") ? Section.GetKey("Name").GetValue().AsString() : Name;
        Data.Description = Section.HasKey("Description") ? Section.GetKey("Description").GetValue().AsString() : "";
        Data.IsUnlocked = Section.HasKey("Unlocked") && Section.GetKey("Unlocked").GetValue().AsBool(false);
        Data.UnlockTimestamp = Section.HasKey("Timestamp") ? Section.GetKey("Timestamp").GetValue().AsInt(0) : 0;
        mAchievements[Name] = Data;
    }

    return true;
}

bool AchievementManager::SaveToFile() const {
    auto FilePath = Common::FileUtils::CombinePath(mStoragePath, "Achievements.ini");
    Ini::IniParser Parser;
    // NOTE: each achievement becomes a section, could get unwieldy with 1000+ achievements
    for (auto& Pair : mAchievements) {
        Parser.SetValue(Pair.first, "Name", Pair.second.Name);
        Parser.SetValue(Pair.first, "Description", Pair.second.Description);
        Parser.SetValue(Pair.first, "Unlocked", Pair.second.IsUnlocked ? "true" : "false");
        Parser.SetValue(Pair.first, "Timestamp", std::to_string(Pair.second.UnlockTimestamp));
    }
    return Parser.Save(FilePath);
}

} // namespace Uues::Core::Storage