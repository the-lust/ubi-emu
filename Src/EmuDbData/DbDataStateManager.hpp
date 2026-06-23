#pragma once

#include "../Core/Config/EmulatorConfig.hpp"

#ifdef _WIN32
    #ifdef EmuDbData_EXPORTS
        #define EMUDBDATA_API __declspec(dllexport)
    #else
        #define EMUDBDATA_API
    #endif
#else
    #define EMUDBDATA_API
#endif

namespace Uues::EmuDbData {

class EMUDBDATA_API DbDataStateManager {
public:
    static DbDataStateManager& GetInstance();
    void SetConfig(const Core::Config::EmulatorConfig& Config);
    Core::Config::EmulatorConfig& GetConfig();
    bool IsInitialized() const;
    void Reset();
private:
    DbDataStateManager() = default;
    DbDataStateManager(const DbDataStateManager&) = delete;
    Core::Config::EmulatorConfig mConfig;
    bool mInitialized = false;
};

} // namespace Uues::EmuDbData