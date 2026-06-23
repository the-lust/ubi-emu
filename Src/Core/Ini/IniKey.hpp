#pragma once

#include "../Common/Types.hpp"
#include "IniValue.hpp"
#include "IniComment.hpp"

namespace Uues::Core::Ini {

class IniKey {
public:
    explicit IniKey(const Common::String& Name = "");

    Common::String GetName() const;
    void SetName(const Common::String& Name);

    IniValue& GetValue();
    const IniValue& GetValue() const;
    void SetValue(const IniValue& Value);

    bool HasComment() const;
    IniComment& GetComment();
    const IniComment& GetComment() const;
    void SetComment(const IniComment& Comment);

private:
    Common::String mName;
    IniValue mValue;
    IniComment mComment;
};

} // namespace Uues::Core::Ini