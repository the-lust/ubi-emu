#include "IniSection.hpp"
#include "../Common/StringUtils.hpp"
#include <algorithm>

namespace Uues::Core::Ini {

IniSection::IniSection(const Common::String& Name) : mName(Name) {}

Common::String IniSection::GetName() const { return mName; }
void IniSection::SetName(const Common::String& Name) { mName = Name; }

bool IniSection::HasKey(const Common::String& Name) const {
    return mKeyIndex.find(Common::StringUtils::ToLower(Name)) != mKeyIndex.end();
}

IniKey& IniSection::GetKey(const Common::String& Name) {
    auto It = mKeyIndex.find(Common::StringUtils::ToLower(Name));
    if (It != mKeyIndex.end() && It->second < mKeys.size()) {
        return mKeys[It->second];
    }
    static IniKey EmptyKey;
    return EmptyKey;
}

const IniKey& IniSection::GetKey(const Common::String& Name) const {
    auto It = mKeyIndex.find(Common::StringUtils::ToLower(Name));
    if (It != mKeyIndex.end() && It->second < mKeys.size()) {
        return mKeys[It->second];
    }
    static IniKey EmptyKey;
    return EmptyKey;
}

void IniSection::AddKey(const IniKey& Key) {
    auto Lower = Common::StringUtils::ToLower(Key.GetName());
    mKeyIndex[Lower] = mKeys.size();
    mKeys.push_back(Key);
}

void IniSection::SetKey(const Common::String& Name, const Common::String& Value) {
    // FIXME: if Name or Value contain newlines, INI breaks
    if (HasKey(Name)) {
        GetKey(Name).SetValue(IniValue(Value));
    } else {
        IniKey NewKey(Name);
        NewKey.SetValue(IniValue(Value));
        AddKey(NewKey);
    }
}

bool IniSection::RemoveKey(const Common::String& Name) {
    auto Lower = Common::StringUtils::ToLower(Name);
    auto It = mKeyIndex.find(Lower);
    if (It == mKeyIndex.end()) return false;
    auto pos = It->second;
    mKeys.erase(mKeys.begin() + pos);
    mKeyIndex.erase(It);
    // TODO: this reindex loop is O(n), could use a lazy rebuild instead
    for (auto& pair : mKeyIndex) {
        if (pair.second > pos) pair.second--;
    }
    return true;
}

size_t IniSection::GetKeyCount() const { return mKeys.size(); }

std::vector<IniKey> IniSection::GetAllKeys() const { return mKeys; }

bool IniSection::HasComment() const { return !mComment.GetText().empty(); }
IniComment& IniSection::GetComment() { return mComment; }
const IniComment& IniSection::GetComment() const { return mComment; }
void IniSection::SetComment(const IniComment& Comment) { mComment = Comment; }

Common::String IniSection::GetValue(const Common::String& Key, const Common::String& Default) const {
    if (!HasKey(Key)) return Default;
    return GetKey(Key).GetValue().AsString();
}

std::vector<std::pair<Common::String, Common::String>> IniSection::GetEntries() const {
    std::vector<std::pair<Common::String, Common::String>> Entries;
    for (const auto& K : mKeys) {
        Entries.emplace_back(K.GetName(), K.GetValue().AsString());
    }
    return Entries;
}

std::vector<IniKey>& IniSection::GetKeys() { return mKeys; }

} // namespace Uues::Core::Ini