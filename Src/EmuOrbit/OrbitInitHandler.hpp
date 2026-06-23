#pragma once

#ifdef _WIN32
    #ifdef EmuOrbit_EXPORTS
        #define EMUORBIT_API __declspec(dllexport)
    #else
        #define EMUORBIT_API
    #endif
#else
    #define EMUORBIT_API
#endif

namespace Uues::EmuOrbit {

class EMUORBIT_API OrbitInitHandler {
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