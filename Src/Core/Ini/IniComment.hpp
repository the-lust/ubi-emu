#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Ini {

class IniComment {
public:
    explicit IniComment(const Common::String& Text = "", bool IsInline = false);

    Common::String GetText() const;
    void SetText(const Common::String& Text);
    bool IsInline() const;
    void SetIsInline(bool Inline);

private:
    Common::String mText;
    bool mIsInline;
};

} // namespace Uues::Core::Ini