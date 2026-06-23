#pragma once

namespace Uues::EmuUPC {

class UpcInitHandler {
public:
    static bool HandleInit(unsigned int Version, int AppId);
    static bool HandleShutdown();
    static bool IsInitialized();
    static unsigned int GetVersion();

private:
    static bool mInitialized;
    static int mAppId;
    static unsigned int mVersion;
};

} // namespace Uues::EmuUPC