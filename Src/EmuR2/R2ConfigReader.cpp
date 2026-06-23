#include "R2ConfigReader.hpp"
#include "../Core/Ini/IniParser.hpp"

namespace Uues::EmuR2 {
using namespace Uues::Core;

R2ConfigReader::R2ConfigReader() {
    mConfig = Core::Config::EmulatorConfig::LoadDefaults();
    mConfig.Type = Core::Config::EmulatorType::R2;
}

bool R2ConfigReader::Load(const Common::String& Path) {
    Core::Ini::IniParser parser;
    if (!parser.Load(Path)) {
        // couldn't load ini, using defaults
        return false;
    }
    return mConfig.LoadFromIni(parser);
}

Core::Config::EmulatorConfig R2ConfigReader::GetConfig() const {
    return mConfig;
}

} // namespace Uues::EmuR2
