#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Storage {

class UserProfile {
public:
    UserProfile();
    ~UserProfile();

    static UserProfile& GetInstance();

    void SetUserId(const Common::String& Id);
    void SetUserName(const Common::String& Name);
    void SetEmail(const Common::String& Email);
    void SetLanguage(const Common::String& Lang);
    void SetAvatar(const Common::String& AvatarId);

    Common::String GetUserId() const;
    Common::String GetUserName() const;
    Common::String GetEmail() const;
    Common::String GetLanguage() const;
    Common::String GetAvatar() const;

    bool IsValid() const;
    void Reset();

private:
    Common::String mUserId;
    Common::String mUserName;
    Common::String mEmail;
    Common::String mLanguage;
    Common::String mAvatar;
};

} // namespace Uues::Core::Storage