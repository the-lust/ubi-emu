#pragma once

#include "../Common/Types.hpp"
#include <functional>
#include <unordered_map>

namespace Uues::Core::Hook {

class MinHookManager {
public:
    static MinHookManager& GetInstance();

    bool Initialize();
    bool HookFunction(const Common::String& ModuleName, const Common::String& FunctionName,
                      void* DetourFunc, void** OriginalFunc);
    bool HookFunction(void* TargetFunc, void* DetourFunc, void** OriginalFunc);
    bool UnhookFunction(void* TargetFunc);
    bool UnhookAll();
    bool IsInitialized() const;

private:
    MinHookManager() = default;
    ~MinHookManager();
    MinHookManager(const MinHookManager&) = delete;
    MinHookManager& operator=(const MinHookManager&) = delete;

    bool mInitialized = false;
    struct HookEntry { void* Target; void* Detour; void* Original; };
    std::vector<HookEntry> mHooks;
};

} // namespace Uues::Core::Hook