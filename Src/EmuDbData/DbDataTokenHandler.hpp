#pragma once

#include "../Core/Common/Types.hpp"
#include "../Core/Crypto/TokenParser.hpp"
#include <unordered_map>

namespace Uues::EmuDbData {

class DbDataTokenHandler {
public:
    static DbDataTokenHandler& GetInstance();

    void SetToken(const Core::Common::String& TokenType, const Uues::Core::Common::ByteArray& TokenData);
    Uues::Core::Common::ByteArray GetToken(const Core::Common::String& TokenType) const;
    bool LoadFromFile(const Core::Common::String& Path);
    bool SaveToFile(const Core::Common::String& Path) const;

private:
    DbDataTokenHandler() = default;
    DbDataTokenHandler(const DbDataTokenHandler&) = delete;
    std::unordered_map<Core::Common::String, Uues::Core::Common::ByteArray> mTokens;
};

} // namespace Uues::EmuDbData