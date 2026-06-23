#include "IniParser.hpp"
#include "../Common/StringUtils.hpp"
#include "../Common/FileUtils.hpp"
#include <algorithm>
#include <sstream>

namespace Uues::Core::Ini {

// TODO: handle escaped chars in values, BOM at start of file, unicode paths
IniParser::IniParser() : m_lineNumber(0), m_warningCount(0) {}

bool IniParser::Load(const Common::String& Path) {
    Common::String Content;
    if (!Common::FileUtils::ReadAllText(Path, Content)) return false;
    return LoadFromString(Content);
}

bool IniParser::LoadFromString(const Common::String& Content) {
    Clear();
    m_lineNumber = 0;
    auto Lines = Common::StringUtils::Split(Content, '\n');
    for (auto& Line : Lines) {
        m_lineNumber++;
        auto Trimmed = Common::StringUtils::Trim(Line);
        if (!Trimmed.empty()) {
            ParseLine(Trimmed);
        }
    }
    RebuildIndex();
    return true;
}

bool IniParser::Save(const Common::String& Path) {
    return Common::FileUtils::WriteAllText(Path, SaveToString());
}

Common::String IniParser::SaveToString() const {
    std::ostringstream Oss;
    for (const auto& Section : mSections) {
        if (Section.HasComment()) {
            Oss << "; " << Section.GetComment().GetText() << "\n";
        }
        Oss << "[" << Section.GetName() << "]\n";
        for (const auto& Key : Section.GetAllKeys()) {
            if (Key.HasComment()) {
                Oss << "; " << Key.GetComment().GetText() << "\n";
            }
            Oss << Key.GetName() << "=" << Key.GetValue().AsString() << "\n";
        }
        Oss << "\n";
    }
    return Oss.str();
}

void IniParser::Clear() {
    mSections.clear();
    mSectionIndex.clear();
}

bool IniParser::HasSection(const Common::String& Name) const {
    return mSectionIndex.find(Common::StringUtils::ToLower(Name)) != mSectionIndex.end();
}

IniSection& IniParser::GetSection(const Common::String& Name) {
    auto Lower = Common::StringUtils::ToLower(Name);
    auto It = mSectionIndex.find(Lower);
    if (It != mSectionIndex.end() && It->second < mSections.size()) {
        return mSections[It->second];
    }
    static IniSection Empty;
    return Empty;
}

const IniSection& IniParser::GetSection(const Common::String& Name) const {
    auto Lower = Common::StringUtils::ToLower(Name);
    auto It = mSectionIndex.find(Lower);
    if (It != mSectionIndex.end() && It->second < mSections.size()) {
        return mSections[It->second];
    }
    static IniSection Empty;
    return Empty;
}

void IniParser::AddSection(const IniSection& Section) {
    if (!HasSection(Section.GetName())) {
        mSectionIndex[Common::StringUtils::ToLower(Section.GetName())] = mSections.size();
        mSections.push_back(Section);
    }
}

bool IniParser::RemoveSection(const Common::String& Name) {
    auto Lower = Common::StringUtils::ToLower(Name);
    auto It = mSectionIndex.find(Lower);
    if (It == mSectionIndex.end()) return false;
    mSections.erase(mSections.begin() + It->second);
    mSectionIndex.erase(It);
    RebuildIndex();
    return true;
}

bool IniParser::HasKey(const Common::String& Section, const Common::String& Key) const {
    if (!HasSection(Section)) return false;
    return GetSection(Section).HasKey(Key);
}

Common::String IniParser::GetValue(const Common::String& Section, const Common::String& Key,
                                    const Common::String& Default) const {
    if (!HasSection(Section)) return Default;
    auto& S = GetSection(Section);
    if (!S.HasKey(Key)) return Default;
    auto Val = S.GetKey(Key).GetValue().AsString();
    return Val.empty() ? Default : Val;
}

void IniParser::SetValue(const Common::String& Section, const Common::String& Key,
                          const Common::String& Value) {
    if (!HasSection(Section)) {
        IniSection NewSection(Section);
        AddSection(NewSection);
    }
    GetSection(Section).SetKey(Key, Value);
}

std::vector<Common::String> IniParser::GetSectionNames() const {
    std::vector<Common::String> Names;
    for (const auto& S : mSections) Names.push_back(S.GetName());
    return Names;
}

size_t IniParser::GetSectionCount() const { return mSections.size(); }

void IniParser::Merge(const IniParser& Other) {
    for (const auto& SectionName : Other.GetSectionNames()) {
        const auto& OtherSection = Other.GetSection(SectionName);
        if (HasSection(SectionName)) {
            auto& ThisSection = GetSection(SectionName);
            for (const auto& Key : OtherSection.GetAllKeys()) {
                ThisSection.SetKey(Key.GetName(), Key.GetValue().AsString());
            }
        } else {
            AddSection(OtherSection);
        }
    }
}

void IniParser::MergeFromFile(const Common::String& Path) {
    IniParser Other;
    if (Other.Load(Path)) Merge(Other);
}

bool IniParser::IsValidSectionName(const Common::String& Name) {
    if (Name.empty() || Name.length() > 256) return false;
    return Name.find_first_of("[]\r\n") == Common::String::npos;
}

bool IniParser::IsValidKeyName(const Common::String& Name) {
    if (Name.empty() || Name.length() > 256) return false;
    return Name.find_first_of("=\r\n") == Common::String::npos;
}

void IniParser::ParseLine(const Common::String& Line) {
    if (Line.empty()) { return; }
    // skip comments
    if (Line[0] == ';' || Line[0] == '#') { return; }
    if (Line[0] == '[') {
        auto Close = Line.find(']');
        if (Close != Common::String::npos && Close > 1) {
            auto Name = Line.substr(1, Close - 1);
            // HACK: we don't validate section name beyond basic bracket check
            AddSection(IniSection(Name));
            return;
        }
        // malformed section header
        m_warningCount++;
    }
    auto EqPos = Line.find('=');
    if (EqPos != Common::String::npos && EqPos > 0) {
        auto KeyName = Common::StringUtils::Trim(Line.substr(0, EqPos));
        auto KeyValue = Common::StringUtils::Trim(Line.substr(EqPos + 1));
        if (!mSections.empty()) {
            mSections.back().SetKey(KeyName, KeyValue);
        }
        // FIXME: what if there's no section yet? silently drops key
    }
}

void IniParser::RebuildIndex() const {
    mSectionIndex.clear();
    for (size_t I = 0; I < mSections.size(); ++I) {
        mSectionIndex[Common::StringUtils::ToLower(mSections[I].GetName())] = I;
    }
}

} // namespace Uues::Core::Ini