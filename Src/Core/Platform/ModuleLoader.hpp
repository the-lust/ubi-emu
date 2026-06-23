#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Platform {

class ModuleLoader {
public:
    static void* LoadLibrary(const Common::String& Path);
    static bool FreeLibrary(void* Handle);
    static void* GetProcAddress(void* Handle, const Common::String& ProcName);
    static void* GetModuleHandle(const Common::String& Name);
    static Common::String GetModulePath(void* Handle);
    static bool IsModuleLoaded(const Common::String& Name);

private:
    ModuleLoader() = delete;
};

} // namespace Uues::Core::Platform