#include "SavePathResolver.hpp"
#include "../Common/FileUtils.hpp"

namespace Uues::Core::Storage {

SavePathResolver::SavePathResolver() {}
SavePathResolver::~SavePathResolver() = default;

void SavePathResolver::SetBasePath(const Common::String& Path) { mBasePath = Path; }
void SavePathResolver::SetAppId(const Common::String& AppId) { mAppId = AppId; }
void SavePathResolver::SetUserId(const Common::String& UserId) { mUserId = UserId; }

Common::String SavePathResolver::Resolve(const Common::String& RelativePath) const {
    auto Path = mBasePath;
    if (!mUserId.empty()) Path = Common::FileUtils::CombinePath(Path, mUserId);
    if (!mAppId.empty()) Path = Common::FileUtils::CombinePath(Path, mAppId);
    if (!RelativePath.empty()) Path = Common::FileUtils::CombinePath(Path, RelativePath);
    // HACK: no sanitization on path components, .. in UserId could escape base path
    return Path;
}

Common::String SavePathResolver::GetAchievementPath() const {
    return Resolve("Achievements");
}

Common::String SavePathResolver::GetProfilePath() const {
    return Resolve("Profile.ini");
}

} // namespace Uues::Core::Storage