#include "IniComment.hpp"

namespace Uues::Core::Ini {

IniComment::IniComment(const Common::String& Text, bool IsInline)
    : mText(Text), mIsInline(IsInline) {
}

Common::String IniComment::GetText() const { return mText; }
void IniComment::SetText(const Common::String& Text) { mText = Text; }

bool IniComment::IsInline() const { return mIsInline; }
void IniComment::SetIsInline(bool Inline) { mIsInline = Inline; }

} // namespace Uues::Core::Ini