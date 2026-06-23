#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Platform {

class LinuxPlatform {
public:
    static Common::String GetHomeDirectory();
    static Common::String GetConfigDirectory();
    static Common::String GetEnvironmentVariable(const Common::String& Name);
    static Common::String GetTempPath();

private:
    LinuxPlatform() = delete;
};

} // namespace Uues::Core::Platform