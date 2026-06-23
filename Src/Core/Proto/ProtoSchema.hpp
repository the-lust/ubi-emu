#pragma once

#include "../Common/Types.hpp"
#include <unordered_map>
#include <vector>

namespace Uues::Core::Proto {

class ProtoSchema {
public:
    ProtoSchema();
    ~ProtoSchema();

    bool LoadFromFile(const Common::String& Path);
    bool LoadFromString(const Common::String& Content);
    bool HasMessage(const Common::String& Name) const;
    std::vector<Common::String> GetFieldNames(const Common::String& MessageName) const;
    int GetFieldNumber(const Common::String& MessageName, const Common::String& FieldName) const;

private:
    struct FieldDef { Common::String Name; int Number; Common::String Type; };
    struct MessageDef { Common::String Name; std::vector<FieldDef> Fields; };
    std::unordered_map<Common::String, MessageDef> mMessages;
};

} // namespace Uues::Core::Proto