#include "DbDataTokenHandler.hpp"
#include "../Core/Ini/IniParser.hpp"
#include "../Core/Common/FileUtils.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuDbData {
using namespace Uues::Core;

DbDataTokenHandler& DbDataTokenHandler::GetInstance() {
    static DbDataTokenHandler Instance;
    return Instance;
}

void DbDataTokenHandler::SetToken(const Common::String& TokenType, const Common::ByteArray& TokenData) {
    if (TokenType.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataToken] Empty token type, storing as 'unnamed'");
        mTokens["unnamed"] = TokenData;
        return;
    }
    if (TokenData.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataToken] Empty data for token '" + TokenType + "', removing");
        mTokens.erase(TokenType);
        return;
    }
    mTokens[TokenType] = TokenData;
    Log::Logger::GetInstance().Info("[DbDataToken] Token '" + TokenType + "' set (" +
        std::to_string(TokenData.size()) + " bytes)");
}

Common::ByteArray DbDataTokenHandler::GetToken(const Common::String& TokenType) const {
    auto It = mTokens.find(TokenType);
    if (It == mTokens.end()) {
        Log::Logger::GetInstance().Debug("[DbDataToken] Token '" + TokenType + "' not found");
        return {};
    }
    return It->second;
}

bool DbDataTokenHandler::LoadFromFile(const Common::String& Path) {
    if (Path.empty()) {
        Log::Logger::GetInstance().Error("[DbDataToken] LoadFromFile called with empty path");
        return false;
    }
    if (!FileUtils::FileExists(Path)) {
        Log::Logger::GetInstance().Warning("[DbDataToken] Token file not found: " + Path);
        return false;
    }

    Core::Ini::IniParser Parser;
    if (!Parser.Load(Path)) {
        Log::Logger::GetInstance().Error("[DbDataToken] Failed to parse token file: " + Path);
        return false;
    }

    if (Parser.HasSection("token")) {
        auto TokenStr = Parser.GetValue("token", "token");
        if (!TokenStr.empty()) {
            mTokens["default"] = Common::ByteArray(TokenStr.begin(), TokenStr.end());
        }
        auto OwnershipStr = Parser.GetValue("token", "ownership");
        if (!OwnershipStr.empty()) {
            mTokens["ownership"] = Common::ByteArray(OwnershipStr.begin(), OwnershipStr.end());
        }
    }

    Log::Logger::GetInstance().Info("[DbDataToken] Loaded " +
        std::to_string(mTokens.size()) + " token(s) from " + Path);
    return true;
}

bool DbDataTokenHandler::SaveToFile(const Common::String& Path) const {
    if (Path.empty()) {
        Log::Logger::GetInstance().Error("[DbDataToken] SaveToFile called with empty path");
        return false;
    }

    Core::Ini::IniParser Parser;

    auto DefaultIt = mTokens.find("default");
    if (DefaultIt != mTokens.end()) {
        Parser.SetValue("token", "token",
            Common::String(DefaultIt->second.begin(), DefaultIt->second.end()));
    }

    auto OwnershipIt = mTokens.find("ownership");
    if (OwnershipIt != mTokens.end()) {
        Parser.SetValue("token", "ownership",
            Common::String(OwnershipIt->second.begin(), OwnershipIt->second.end()));
    }

    if (!Parser.Save(Path)) {
        Log::Logger::GetInstance().Error("[DbDataToken] Failed to save to " + Path);
        return false;
    }

    Log::Logger::GetInstance().Info("[DbDataToken] Saved tokens to " + Path);
    return true;
}

} // namespace Uues::EmuDbData
