#pragma once

#include "../Common/Types.hpp"
#include "IniSection.hpp"
#include <vector>
#include <unordered_map>

namespace Uues::Core::Ini {

class IniParser {
public:
    IniParser();

    bool Load(const Common::String& Path);
    bool LoadFromString(const Common::String& Content);
    bool Save(const Common::String& Path);
    Common::String SaveToString() const;
    void Clear();

    bool HasSection(const Common::String& Name) const;
    IniSection& GetSection(const Common::String& Name);
    const IniSection& GetSection(const Common::String& Name) const;
    void AddSection(const IniSection& Section);
    bool RemoveSection(const Common::String& Name);

    bool HasKey(const Common::String& Section, const Common::String& Key) const;
    Common::String GetValue(const Common::String& Section, const Common::String& Key,
                            const Common::String& Default = "") const;
    void SetValue(const Common::String& Section, const Common::String& Key,
                  const Common::String& Value);

    std::vector<Common::String> GetSectionNames() const;
    size_t GetSectionCount() const;

    void Merge(const IniParser& Other);
    void MergeFromFile(const Common::String& Path);

    static bool IsValidSectionName(const Common::String& Name);
    static bool IsValidKeyName(const Common::String& Name);

private:
    void ParseLine(const Common::String& Line);

    std::vector<IniSection> mSections;
    mutable std::unordered_map<Common::String, size_t> mSectionIndex;
    int m_lineNumber = 0;
    int m_warningCount = 0;
    void RebuildIndex() const;
};

} // namespace Uues::Core::Ini