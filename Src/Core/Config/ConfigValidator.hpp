#pragma once

#include "../Common/Types.hpp"
#include "EmulatorConfig.hpp"
#include "../Ini/IniParser.hpp"

namespace Uues::Core::Config {

struct ConfigValidationResult {
    bool IsValid;
    Common::StringList Warnings;
    Common::StringList Errors;
};

class ConfigValidator {
public:
    static ConfigValidationResult Validate(const Ini::IniParser& Parser);
    static ConfigValidationResult Validate(const EmulatorConfig& Config);
    static bool ValidateUserId(const Common::String& UserId);
    static bool ValidateEmail(const Common::String& Email);
    static bool ValidatePort(uint16_t Port);

private:
    ConfigValidator() = delete;
};

} // namespace Uues::Core::Config