#pragma once

#include "../Common/Types.hpp"
#include "UserProfile.hpp"
#include "../Ini/IniParser.hpp"

namespace Uues::Core::Storage {

class ProfileSerializer {
public:
    static bool Save(const UserProfile& Profile, const Common::String& Path);
    static bool Load(UserProfile& Profile, const Common::String& Path);
    static UserProfile FromIni(const Ini::IniParser& Parser);
    static Ini::IniParser ToIni(const UserProfile& Profile);

private:
    ProfileSerializer() = delete;
};

} // namespace Uues::Core::Storage