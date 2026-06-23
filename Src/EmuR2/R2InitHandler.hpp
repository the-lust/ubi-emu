#pragma once

namespace Uues::EmuR2 {

class R2InitHandler {
public:
    static bool HandleInit(unsigned int Version, int AppId);
    static bool HandleShutdown();
    static bool IsInitialized();

private:
    static bool mInitialized;
    static int mAppId;
};

} // namespace Uues::EmuR2