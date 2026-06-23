#pragma once

namespace Uues::EmuDbData {

class DbDataInitHandler {
public:
    static bool HandleInit(const char* Config);
    static bool HandleShutdown();
    static bool IsInitialized();

private:
    static bool mInitialized;
    static Core::Common::String mConfigString;
};

} // namespace Uues::EmuDbData