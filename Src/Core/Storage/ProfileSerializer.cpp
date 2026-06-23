#include "ProfileSerializer.hpp"

namespace Uues::Core::Storage {

bool ProfileSerializer::Save(const UserProfile& Profile, const Common::String& Path) {
    auto Parser = ToIni(Profile);
    return Parser.Save(Path);
}

bool ProfileSerializer::Load(UserProfile& Profile, const Common::String& Path) {
    Ini::IniParser Parser;
    // FIXME: if the file is corrupted, this silently returns a default profile
    if (!Parser.Load(Path)) return false;
    Profile = FromIni(Parser);
    return true;
}

UserProfile ProfileSerializer::FromIni(const Ini::IniParser& Parser) {
    UserProfile Profile;
    if (Parser.HasSection("Profile")) {
        auto& S = Parser.GetSection("Profile");
        if (S.HasKey("UserId")) Profile.SetUserId(S.GetKey("UserId").GetValue().AsString());
        if (S.HasKey("UserName")) Profile.SetUserName(S.GetKey("UserName").GetValue().AsString());
        if (S.HasKey("Email")) Profile.SetEmail(S.GetKey("Email").GetValue().AsString());
        if (S.HasKey("Language")) Profile.SetLanguage(S.GetKey("Language").GetValue().AsString());
        if (S.HasKey("Avatar")) Profile.SetAvatar(S.GetKey("Avatar").GetValue().AsString());
    }
    return Profile;
}

Ini::IniParser ProfileSerializer::ToIni(const UserProfile& Profile) {
    Ini::IniParser Parser;
    Parser.SetValue("Profile", "UserId", Profile.GetUserId());
    Parser.SetValue("Profile", "UserName", Profile.GetUserName());
    Parser.SetValue("Profile", "Email", Profile.GetEmail());
    Parser.SetValue("Profile", "Language", Profile.GetLanguage());
    Parser.SetValue("Profile", "Avatar", Profile.GetAvatar());
    return Parser;
}

} // namespace Uues::Core::Storage