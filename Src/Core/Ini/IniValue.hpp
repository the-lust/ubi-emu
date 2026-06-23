#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Ini {

class IniValue {
public:
    explicit IniValue(const Common::String& Raw = "");

    Common::String AsString() const;
    int AsInt(int Default = 0) const;
    unsigned int AsUint(unsigned int Default = 0) const;
    bool AsBool(bool Default = false) const;
    Common::StringList AsList(char Delimiter = ',') const;

    void Set(const Common::String& Value);
    void Set(int Value);
    void Set(unsigned int Value);
    void Set(bool Value);

    bool IsEmpty() const;

private:
    Common::String mRaw;
};

} // namespace Uues::Core::Ini