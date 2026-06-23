#pragma once

namespace Uues::EmuOrbit {

class OrbitInitHandler {
public:
    static bool HandleInit(unsigned int Version, int AppId);
    static bool HandleShutdown();
    static bool IsInitialized();

private:
    static bool mInitialized;
    static int mAppId;
    static unsigned int mSdkVersion;
};

} // namespace Uues::EmuOrbit