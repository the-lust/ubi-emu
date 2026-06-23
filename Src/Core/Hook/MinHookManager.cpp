#include "MinHookManager.hpp"
#include <MinHook.h>
#include "Log/Logger.hpp"

namespace Uues::Core::Hook {

MinHookManager& MinHookManager::GetInstance() {
    static MinHookManager Instance;
    return Instance;
}

MinHookManager::~MinHookManager() {
    UnhookAll();
}

bool MinHookManager::Initialize() {
    if (mInitialized) return true;
    MH_STATUS Status = MH_Initialize();
    mInitialized = (Status == MH_OK);
    return mInitialized;
}

bool MinHookManager::HookFunction(const Common::String& ModuleName, const Common::String& FunctionName,
                                   void* DetourFunc, void** OriginalFunc) {
    HMODULE Module = GetModuleHandleA(ModuleName.c_str());
    if (!Module) return false;
    void* TargetFunc = reinterpret_cast<void*>(GetProcAddress(Module, FunctionName.c_str()));
    if (!TargetFunc) return false;
    return HookFunction(TargetFunc, DetourFunc, OriginalFunc);
}

bool MinHookManager::HookFunction(void* TargetFunc, void* DetourFunc, void** OriginalFunc) {
    if (!mInitialized && !Initialize()) {
        return false;
    }

    // NOTE: MH_CreateHook allocates a trampoline, this can fail if memory is tight
    MH_STATUS Status = MH_CreateHook(TargetFunc, DetourFunc, OriginalFunc);
    if (Status != MH_OK) {
        return false;
    }

    Status = MH_EnableHook(TargetFunc);
    if (Status != MH_OK) {
        MH_RemoveHook(TargetFunc);
        return false;
    }

    mHooks.push_back({TargetFunc, DetourFunc, OriginalFunc ? *OriginalFunc : nullptr});
    return true;
}

bool MinHookManager::UnhookFunction(void* TargetFunc) {
    MH_STATUS Status = MH_DisableHook(TargetFunc);
    if (Status == MH_OK) {
        MH_RemoveHook(TargetFunc);
    }
    auto It = std::remove_if(mHooks.begin(), mHooks.end(),
        [TargetFunc](const HookEntry& E) { return E.Target == TargetFunc; });
    mHooks.erase(It, mHooks.end());
    return Status == MH_OK;
}

bool MinHookManager::UnhookAll() {
    if (!mInitialized) return true;
    MH_Uninitialize();
    mHooks.clear();
    mInitialized = false;
    return true;
}

bool MinHookManager::IsInitialized() const { return mInitialized; }

} // namespace Uues::Core::Hook