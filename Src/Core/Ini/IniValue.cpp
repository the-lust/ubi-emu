#include "IniValue.hpp"
#include "../Common/StringUtils.hpp"

namespace Uues::Core::Ini {

IniValue::IniValue(const Common::String& Raw) : mRaw(Raw) {}

Common::String IniValue::AsString() const { return mRaw; }

int IniValue::AsInt(int Default) const {
    int result;
    // TODO: does TryParseInt handle hex? 0xFF would be useful
    return Common::StringUtils::TryParseInt(mRaw, result) ? result : Default;
}

unsigned int IniValue::AsUint(unsigned int Default) const {
    unsigned int result;
    return Common::StringUtils::TryParseUint(mRaw, result) ? result : Default;
}

bool IniValue::AsBool(bool Default) const {
    auto lower = Common::StringUtils::ToLower(Common::StringUtils::Trim(mRaw));
    if (lower == "true" || lower == "1" || lower == "yes") return true;
    if (lower == "false" || lower == "0" || lower == "no") return false;
    // HACK: anything else falls back to default, maybe we should warn
    return Default;
}

Common::StringList IniValue::AsList(char Delimiter) const {
    auto Parts = Common::StringUtils::Split(mRaw, Delimiter);
    Common::StringList Result;
    for (auto& Part : Parts) {
        auto Trimmed = Common::StringUtils::Trim(Part);
        if (!Trimmed.empty()) Result.push_back(Trimmed);
    }
    // FIXME: quoted values with embedded delimiters will be split incorrectly
    return Result;
}

void IniValue::Set(const Common::String& Value) { mRaw = Value; }
void IniValue::Set(int Value) { mRaw = std::to_string(Value); }
void IniValue::Set(unsigned int Value) { mRaw = std::to_string(Value); }
void IniValue::Set(bool Value) { mRaw = Value ? "true" : "false"; }
bool IniValue::IsEmpty() const { return mRaw.empty(); }

} // namespace Uues::Core::Ini