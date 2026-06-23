#pragma once

#include "../Core/Common/Types.hpp"

#ifdef _WIN32
    #ifdef EmuShared_EXPORTS
        #define EMUSHARED_API __declspec(dllexport)
    #else
        #define EMUSHARED_API __declspec(dllimport)
    #endif
#else
    #define EMUSHARED_API
#endif

namespace Uues::Shared {

// Interface version: v1 (stable, used since UUES 1.0)
// If we ever break ABI we'll bump this; for now all emulators implement v1
class EMUSHARED_API EmulatorInterface {
public:
    virtual ~EmulatorInterface() = default;
    virtual bool Initialize() = 0;
    virtual bool Shutdown() = 0;
    virtual bool IsInitialized() const = 0;
    virtual Core::Common::String GetName() const = 0;
    virtual Core::Common::String GetVersion() const = 0;
    virtual bool LoadConfig(const Core::Common::String& ConfigPath) = 0;
};

} // namespace Uues::Shared