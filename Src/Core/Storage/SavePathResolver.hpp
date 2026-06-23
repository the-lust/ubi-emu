#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Storage {

class SavePathResolver {
public:
    SavePathResolver();
    ~SavePathResolver();

    void SetBasePath(const Common::String& Path);
    void SetAppId(const Common::String& AppId);
    void SetUserId(const Common::String& UserId);
    Common::String Resolve(const Common::String& RelativePath = "") const;
    Common::String GetAchievementPath() const;
    Common::String GetProfilePath() const;

private:
    Common::String mBasePath;
    Common::String mAppId;
    Common::String mUserId;
};

} // namespace Uues::Core::Storage