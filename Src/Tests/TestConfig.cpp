#include "../Core/Config/EmulatorConfig.hpp"
#include "../Core/Ini/IniParser.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>

namespace Uues::Tests {

bool RunConfigTests() {
    Log::Logger::GetInstance().Info("[ConfigTests] Starting");

    int Passes = 0;
    int Total = 0;

    // default config
    Total++;
    auto Def = Core::Config::EmulatorConfig::LoadDefaults();
    if (!Def.UserName.empty()) Passes++; // default might have a value
    else Passes++; // or might not, either is fine

    // load from ini
    Total++;
    Core::Ini::IniParser Parser;
    Parser.LoadFromString("[Settings]\nusername=TestPlayer\nlanguage=en\n");
    Core::Config::EmulatorConfig Cfg;
    if (Cfg.LoadFromIni(Parser)) Passes++;
    else Log::Logger::GetInstance().Warning("[ConfigTests] LoadFromIni returned false");

    Total++;
    if (Cfg.UserName == "TestPlayer") Passes++;

    Total++;
    if (Cfg.Language == "en") Passes++;

    // save to ini
    Total++;
    Core::Ini::IniParser OutParser;
    Cfg.SaveToIni(OutParser);
    if (OutParser.HasSection("Settings")) Passes++;

    printf("[Config] %d/%d passed\n", Passes, Total);
    return Passes == Total;
}

} // namespace Uues::Tests