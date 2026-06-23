#include "ProtoSchema.hpp"
#include "../Common/StringUtils.hpp"
#include "../Common/FileUtils.hpp"
#include "../Ini/IniParser.hpp"

namespace Uues::Core::Proto {

ProtoSchema::ProtoSchema() {}
ProtoSchema::~ProtoSchema() = default;

bool ProtoSchema::LoadFromFile(const Common::String& Path) {
    Common::String Content;
    return Common::FileUtils::ReadAllText(Path, Content) && LoadFromString(Content);
}

bool ProtoSchema::LoadFromString(const Common::String& Content) {
    // NOTE: this is a very basic proto schema parser, doesn't support nested messages, imports, etc.
    auto Lines = Common::StringUtils::Split(Content, '\n');
    Common::String CurrentMessage;
    for (auto& Line : Lines) {
        auto Trimmed = Common::StringUtils::Trim(Line);
        if (Trimmed.empty() || Trimmed[0] == '#') continue;
        if (Common::StringUtils::StartsWith(Trimmed, "message ")) {
            CurrentMessage = Trimmed.substr(8);
            auto Brace = CurrentMessage.find('{');
            if (Brace != Common::String::npos) CurrentMessage = Common::StringUtils::Trim(CurrentMessage.substr(0, Brace));
        } else if (Trimmed == "}" || Trimmed == "};") {
            CurrentMessage.clear();
        } else if (!CurrentMessage.empty()) {
            auto Parts = Common::StringUtils::Split(Trimmed, '=');
            if (Parts.size() == 2) {
                auto NameParts = Common::StringUtils::Split(Common::StringUtils::Trim(Parts[0]), ' ');
                if (NameParts.size() >= 2) {
                    FieldDef Def;
                    Def.Type = NameParts[0];
                    Def.Name = NameParts[1];
                    auto NumberStr = Common::StringUtils::Trim(Parts[1]);
                    auto Semi = NumberStr.find(';');
                    if (Semi != Common::String::npos) NumberStr = NumberStr.substr(0, Semi);
                    Def.Number = std::stoi(NumberStr);
                    mMessages[CurrentMessage].Name = CurrentMessage;
                    mMessages[CurrentMessage].Fields.push_back(Def);
                }
            }
        }
    }
    return !mMessages.empty();
}

bool ProtoSchema::HasMessage(const Common::String& Name) const {
    return mMessages.find(Name) != mMessages.end();
}

std::vector<Common::String> ProtoSchema::GetFieldNames(const Common::String& MessageName) const {
    std::vector<Common::String> Names;
    auto It = mMessages.find(MessageName);
    if (It != mMessages.end()) {
        for (auto& F : It->second.Fields) Names.push_back(F.Name);
    }
    return Names;
}

int ProtoSchema::GetFieldNumber(const Common::String& MessageName, const Common::String& FieldName) const {
    auto It = mMessages.find(MessageName);
    if (It != mMessages.end()) {
        for (auto& F : It->second.Fields) {
            if (F.Name == FieldName) return F.Number;
        }
    }
    return -1;
}

} // namespace Uues::Core::Proto