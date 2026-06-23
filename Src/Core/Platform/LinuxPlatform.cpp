#include "LinuxPlatform.hpp"
#include <cstdlib>

namespace Uues::Core::Platform {

Common::String LinuxPlatform::GetHomeDirectory() {
    auto Home = std::getenv("HOME");
    return Home ? Common::String(Home) : "/tmp";  // HACK: fallback to /tmp isn't great
}

Common::String LinuxPlatform::GetConfigDirectory() {
    auto Config = std::getenv("XDG_CONFIG_HOME");
    if (Config) return Common::String(Config);
    return GetHomeDirectory() + "/.config";
}

Common::String LinuxPlatform::GetEnvironmentVariable(const Common::String& Name) {
    auto Val = std::getenv(Name.c_str());
    return Val ? Common::String(Val) : "";
}

Common::String LinuxPlatform::GetTempPath() {
    auto Tmp = std::getenv("TMPDIR");
    return Tmp ? Common::String(Tmp) : "/tmp";
}

} // namespace Uues::Core::Platform