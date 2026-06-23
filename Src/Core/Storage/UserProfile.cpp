#include "UserProfile.hpp"
#include "../Common/GuidGenerator.hpp"

namespace Uues::Core::Storage {

UserProfile::UserProfile() { Reset(); }
UserProfile::~UserProfile() = default;

UserProfile& UserProfile::GetInstance() {
    static UserProfile Instance;
    return Instance;
}

void UserProfile::SetUserId(const Common::String& Id) { mUserId = Id; }
void UserProfile::SetUserName(const Common::String& Name) { mUserName = Name; }
void UserProfile::SetEmail(const Common::String& Email) { mEmail = Email; }
void UserProfile::SetLanguage(const Common::String& Lang) { mLanguage = Lang; }
void UserProfile::SetAvatar(const Common::String& AvatarId) { mAvatar = AvatarId; }

Common::String UserProfile::GetUserId() const {
    // NOTE: generates a new GUID every call if mUserId is empty, that's probably a bug
    return mUserId.empty() ? Common::GuidGenerator::CreateString() : mUserId;
}
Common::String UserProfile::GetUserName() const { return mUserName.empty() ? "Player" : mUserName; }
Common::String UserProfile::GetEmail() const { return mEmail.empty() ? "player@local.host" : mEmail; }
Common::String UserProfile::GetLanguage() const { return mLanguage.empty() ? "en-US" : mLanguage; }
Common::String UserProfile::GetAvatar() const { return mAvatar; }

bool UserProfile::IsValid() const { return !mUserId.empty(); }

void UserProfile::Reset() {
    mUserId = Common::GuidGenerator::CreateString();
    mUserName = "Player";
    mEmail = "player@local.host";
    mLanguage = "en-US";
    mAvatar.clear();
}

} // namespace Uues::Core::Storage