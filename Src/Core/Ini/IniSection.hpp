#pragma once

#include "../Common/Types.hpp"
#include "IniKey.hpp"
#include "IniComment.hpp"
#include <vector>
#include <unordered_map>

namespace Uues::Core::Ini {

class IniSection {
public:
    explicit IniSection(const Common::String& Name = "");

    Common::String GetName() const;
    void SetName(const Common::String& Name);

    bool HasKey(const Common::String& Name) const;
    IniKey& GetKey(const Common::String& Name);
    const IniKey& GetKey(const Common::String& Name) const;
    void AddKey(const IniKey& Key);
    void SetKey(const Common::String& Name, const Common::String& Value);
    bool RemoveKey(const Common::String& Name);

    size_t GetKeyCount() const;
    std::vector<IniKey> GetAllKeys() const;

    bool HasComment() const;
    IniComment& GetComment();
    const IniComment& GetComment() const;
    void SetComment(const IniComment& Comment);

    Common::String GetValue(const Common::String& Key, const Common::String& Default) const;
    std::vector<std::pair<Common::String, Common::String>> GetEntries() const;

    std::vector<IniKey>& GetKeys();

private:
    Common::String mName;
    std::vector<IniKey> mKeys;
    std::unordered_map<Common::String, size_t> mKeyIndex;
    IniComment mComment;
};

} // namespace Uues::Core::Ini