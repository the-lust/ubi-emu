#include "IniKey.hpp"

namespace Uues::Core::Ini {

IniKey::IniKey(const Common::String& Name) : mName(Name) {
    // HACK: empty name keys will silently fail lookups, should we reject?
}

Common::String IniKey::GetName() const { return mName; }
void IniKey::SetName(const Common::String& Name) { mName = Name; }

IniValue& IniKey::GetValue() { return mValue; }
const IniValue& IniKey::GetValue() const { return mValue; }
void IniKey::SetValue(const IniValue& Value) { mValue = Value; }

bool IniKey::HasComment() const { return !mComment.GetText().empty(); }
IniComment& IniKey::GetComment() { return mComment; }
const IniComment& IniKey::GetComment() const { return mComment; }
void IniKey::SetComment(const IniComment& Comment) { mComment = Comment; }

} // namespace Uues::Core::Ini