#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuDbData {

class DbDataInitHandler {
public:
    static bool HandleInit(const char* Config);
    static bool HandleShutdown();
    static bool IsInitialized();

private:
    static bool mInitialized;
    static Uues::Core::Common::String mConfigString;
};

} // namespace Uues::EmuDbData