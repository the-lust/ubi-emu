#include "../Core/Ini/IniParser.hpp"
#include "../Core/Common/FileUtils.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>
#include <cassert>

namespace Uues::Tests {

bool RunIniParserTests() {
    Log::Logger::GetInstance().Info("[IniParserTests] Starting");

    int Fails = 0;

    // parse from string
    Core::Ini::IniParser Parser;
    bool Loaded = Parser.LoadFromString(
        "[Section1]\n"
        "key1=value1\n"
        "key2=value2\n"
        "\n"
        "[Section2]\n"
        "foo=bar\n"
    );
    if (!Loaded) { Fails++; }

    if (Parser.GetSectionCount() != 2) Fails++;
    if (!Parser.HasSection("Section1")) Fails++;
    if (!Parser.HasSection("Section2")) Fails++;
    if (Parser.GetValue("Section1", "key1") != "value1") Fails++;
    if (Parser.GetValue("Section2", "foo") != "bar") Fails++;
    if (Parser.GetValue("Section1", "nonexistent") != "") Fails++;

    // round-trip via string
    Core::Ini::IniParser Parser2;
    auto Saved = Parser.SaveToString();
    Parser2.LoadFromString(Saved);
    if (Parser2.GetSectionCount() != 2) Fails++;
    if (Parser2.GetValue("Section1", "key1") != "value1") Fails++;

    // clear
    Parser.Clear();
    if (Parser.GetSectionCount() != 0) Fails++;

    printf("[IniParser] %s\n", Fails == 0 ? "ALL PASS" : "SOME FAILED");
    return Fails == 0;
}

} // namespace Uues::Tests