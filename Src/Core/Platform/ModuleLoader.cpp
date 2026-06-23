#include "ModuleLoader.hpp"
#include <windows.h>

namespace Uues::Core::Platform {

void* ModuleLoader::LoadLibrary(const Common::String& Path) {
    auto WidePath = Common::StringUtils::ToWide(Path);
    // TODO: use LoadLibraryEx with LOAD_LIBRARY_SEARCH flags for safer loading
    return reinterpret_cast<void*>(::LoadLibraryW(WidePath.c_str()));
}

bool ModuleLoader::FreeLibrary(void* Handle) {
    return ::FreeLibrary(reinterpret_cast<HMODULE>(Handle)) != 0;
}

void* ModuleLoader::GetProcAddress(void* Handle, const Common::String& ProcName) {
    return reinterpret_cast<void*>(::GetProcAddress(
        reinterpret_cast<HMODULE>(Handle), ProcName.c_str()));
}

void* ModuleLoader::GetModuleHandle(const Common::String& Name) {
    auto WideName = Common::StringUtils::ToWide(Name);
    return reinterpret_cast<void*>(::GetModuleHandleW(WideName.c_str()));
}

Common::String ModuleLoader::GetModulePath(void* Handle) {
    wchar_t Path[MAX_PATH];
    GetModuleFileNameW(reinterpret_cast<HMODULE>(Handle), Path, MAX_PATH);
    return Common::StringUtils::FromWide(Path);
}

bool ModuleLoader::IsModuleLoaded(const Common::String& Name) {
    return GetModuleHandle(Name) != nullptr;
}

} // namespace Uues::Core::Platform