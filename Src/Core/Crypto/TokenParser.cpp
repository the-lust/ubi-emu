#include "TokenParser.hpp"
#include "../Ini/IniParser.hpp"
#include "../Common/FileUtils.hpp"
#include "../Common/TimeUtils.hpp"
#include "../Common/StringUtils.hpp"

namespace Uues::Core::Crypto {

bool TokenParser::LoadFromFile(const Common::String& Path) {
    Uues::Core::Ini::IniParser Parser;
    if (!Parser.Load(Path)) return false;

    if (Parser.HasSection("token")) {
        mCached.Token = Parser.GetValue("token", "token");
        mCached.Ownership = Parser.GetValue("token", "ownership");
        auto Expires = Parser.GetValue("token", "expires");
        if (!Expires.empty()) {
            mCached.ExpiresAt = std::stoll(Expires);
        }
    }

    if (Parser.HasSection("settings")) {
        mCached.AppId = Parser.GetValue("settings", "appid");
        auto DlcStr = Parser.GetValue("settings", "dlcs");
        if (!DlcStr.empty()) {
            mCached.Dlcs = Common::StringUtils::Split(DlcStr, ',');
            for (auto& D : mCached.Dlcs) D = Common::StringUtils::Trim(D);
        }
    }

    mCached.IsValid = !mCached.Token.empty();
    return mCached.IsValid;
}

bool TokenParser::SaveToFile(const Common::String& Path) const {
    Uues::Core::Ini::IniParser Parser;
    Parser.SetValue("token", "token", mCached.Token);
    if (!mCached.Ownership.empty()) {
        Parser.SetValue("token", "ownership", mCached.Ownership);
    }
    if (mCached.ExpiresAt > 0) {
        Parser.SetValue("token", "expires", std::to_string(mCached.ExpiresAt));
    }
    if (!mCached.AppId.empty()) {
        Parser.SetValue("settings", "appid", mCached.AppId);
    }
    if (!mCached.Dlcs.empty()) {
        Parser.SetValue("settings", "dlcs", Common::StringUtils::Join(mCached.Dlcs, ","));
    }
    return Parser.Save(Path);
}

bool TokenParser::ParseToken(const Common::String& RawToken, TokenData& Out) const {
    if (RawToken.empty()) {
        return false;
    }
    // TODO: real token parsing (JWT? base64? right now we just store raw)
    Out.Token = RawToken;
    Out.IsValid = true;
    return true;
}

Common::String TokenParser::SerializeToken(const TokenData& Token) const {
    (void)Token;
    return mCached.Token;
}

bool TokenParser::IsExpired(const TokenData& Token) const {
    if (Token.ExpiresAt == 0) return false;
    return Common::TimeUtils::GetCurrentTimestamp() > Token.ExpiresAt;
}

} // namespace Uues::Core::Crypto