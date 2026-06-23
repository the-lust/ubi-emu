#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Crypto {

struct TokenData {
    Common::String Token;
    Common::String Ownership;
    int64_t ExpiresAt = 0;
    Common::String AppId;
    Common::StringList Dlcs;
    bool IsValid = false;
};

class TokenParser {
public:
    bool LoadFromFile(const Common::String& Path);
    bool SaveToFile(const Common::String& Path) const;
    bool ParseToken(const Common::String& RawToken, TokenData& Out) const;
    Common::String SerializeToken(const TokenData& Token) const;
    bool IsExpired(const TokenData& Token) const;

private:
    TokenData mCached;
};

} // namespace Uues::Core::Crypto