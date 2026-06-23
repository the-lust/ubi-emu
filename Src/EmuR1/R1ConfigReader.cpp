#include "R1ConfigReader.hpp"
#include "../Core/Ini/IniParser.hpp"
#include "../Core/Common/FileUtils.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

R1ConfigReader::R1ConfigReader() : mConfig(Config::EmulatorConfig::LoadDefaults()) {
    mConfig.Type = Config::EmulatorType::R1;
}

R1ConfigReader::~R1ConfigReader() = default;

bool R1ConfigReader::Load(const Common::String& Path) {
    Ini::IniParser parser;
    if (!parser.Load(Path)) {
        // Try Ubi.ini as fallback - some old games use this naming
        auto dirName = Common::FileUtils::GetDirectoryName(Path);
        auto ubiPath = Common::FileUtils::CombinePath(dirName, "Ubi.ini");
        if (!parser.Load(ubiPath)) {
            Log::Logger::GetInstance().Warning("[R1Config] Failed to load config from: " + Path);
            return false;
        }
    }
    return LoadFromIni(parser);
}

bool R1ConfigReader::LoadFromIni(const Ini::IniParser& Parser) {
    return mConfig.LoadFromIni(Parser);
}

Config::EmulatorConfig R1ConfigReader::GetConfig() const { return mConfig; }

} // namespace Uues::EmuR1
