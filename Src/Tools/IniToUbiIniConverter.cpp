#include "IniToUbiIniConverter.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Common/FileUtils.hpp"
#include <unordered_map>

namespace Uues::Tools {
using namespace Uues::Core;

// Maps known generic INI keys to UbiIni format keys
const static std::unordered_map<Common::String, Common::String> sKeyMap = {
    { "username",   "ubisoft_account_name" },
    { "userid",     "ubisoft_account_id" },
    { "language",   "locale" },
    { "savedir",    "savegame_directory" },
    { "appid",      "product_id" },
    { "dlc",        "content_ids" },
};

bool IniToUbiIniConverter::Convert(const Ini::IniParser& Source, Ini::IniParser& Output) {
    Log::Logger::GetInstance().Info("[Converter] Starting generic -> UbiIni conversion");

    Output.AddSection(Ini::IniSection("UbiIni"));
    for (auto& Name : Source.GetSectionNames()) {
        if (Name == "Settings" || Name == "General") {
            auto& Sec = Source.GetSection(Name);
            for (auto& [K, V] : Sec.GetEntries()) {
                auto It = sKeyMap.find(K);
                Common::String NewKey = (It != sKeyMap.end()) ? It->second : K;
                Output.SetValue("UbiIni", NewKey, V);
            }
        } else {
            // pass through non-standard sections as-is
            Output.AddSection(Source.GetSection(Name));
        }
    }

    Log::Logger::GetInstance().Info("[Converter] Conversion complete (" +
        std::to_string(Source.GetSectionCount()) + " sections)");
    return true;
}

bool IniToUbiIniConverter::SaveToFile(Ini::IniParser& Parser, const Common::String& OutputPath) {
    if (OutputPath.empty()) {
        Log::Logger::GetInstance().Error("[Converter] SaveToFile: empty output path");
        return false;
    }
    bool Ok = Parser.Save(OutputPath);
    if (Ok) {
        Log::Logger::GetInstance().Info("[Converter] Saved to '" + OutputPath + "'");
    } else {
        Log::Logger::GetInstance().Error("[Converter] Failed to save to '" + OutputPath + "'");
    }
    return Ok;
}

} // namespace Uues::Tools
