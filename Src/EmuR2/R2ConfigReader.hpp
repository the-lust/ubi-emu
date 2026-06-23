#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

namespace Uues::EmuR2 {

class R2ConfigReader {
public:
    R2ConfigReader();
    bool Load(const Core::Common::String& Path);
    Core::Config::EmulatorConfig GetConfig() const; // returns copy, not ref
private:
    Core::Config::EmulatorConfig mConfig;
};

} // namespace Uues::EmuR2