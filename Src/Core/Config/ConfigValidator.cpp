#include "ConfigValidator.hpp"
#include "../Common/GuidGenerator.hpp"
#include "../Common/StringUtils.hpp"
#include <algorithm>

namespace Uues::Core::Config {

ConfigValidationResult ConfigValidator::Validate(const Ini::IniParser& Parser) {
    ConfigValidationResult Result;
    Result.IsValid = true;

    if (!Parser.HasSection("Settings")) {
        Result.Errors.push_back("Missing [Settings] section");
        Result.IsValid = false;
    } else {
        auto& S = Parser.GetSection("Settings");
        if (S.HasKey("UserId") && !ValidateUserId(S.GetKey("UserId").GetValue().AsString())) {
            Result.Warnings.push_back("UserId format may be invalid");
        }
    }

    if (Parser.HasSection("Network")) {
        auto& N = Parser.GetSection("Network");
        if (N.HasKey("ServerPort")) {
            auto Port = N.GetKey("ServerPort").GetValue().AsUint();
            if (!ValidatePort(static_cast<uint16_t>(Port))) {
                Result.Warnings.push_back("ServerPort out of valid range (1024-65535)");
            }
        }
    }

    return Result;
}

ConfigValidationResult ConfigValidator::Validate(const EmulatorConfig& Config) {
    ConfigValidationResult Result;
    Result.IsValid = true;
    if (Config.SavePath.empty()) {
        Result.Warnings.push_back("SavePath is empty, using default");
    }
    return Result;
}

bool ConfigValidator::ValidateUserId(const Common::String& UserId) {
    return Common::GuidGenerator::IsValid(UserId);
}

bool ConfigValidator::ValidateEmail(const Common::String& Email) {
    // FIXME: this is a very basic check, doesn't validate RFC 5322
    auto AtPos = Email.find('@');
    auto DotPos = Email.rfind('.');
    return AtPos != Common::String::npos && DotPos != Common::String::npos && AtPos < DotPos;
}

bool ConfigValidator::ValidatePort(uint16_t Port) {
    return Port >= 1024 && Port <= 65535;
}

} // namespace Uues::Core::Config