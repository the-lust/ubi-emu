#include "WindowsPlatform.hpp"
#include <windows.h>
#include <shlobj.h>

namespace Uues::Core::Platform {

Common::String WindowsPlatform::GetModulePath(HMODULE Module) {
    wchar_t Path[MAX_PATH];
    GetModuleFileNameW(Module, Path, MAX_PATH);  // TODO: MAX_PATH is too short for long paths
    return Common::StringUtils::FromWide(Path);
}

Common::String WindowsPlatform::GetSystemDirectory() {
    wchar_t Path[MAX_PATH];
    GetSystemDirectoryW(Path, MAX_PATH);
    return Common::StringUtils::FromWide(Path);
}

Common::String WindowsPlatform::GetEnvironmentVariable(const Common::String& Name) {
    auto WideName = Common::StringUtils::ToWide(Name);
    wchar_t Buffer[4096];
    Dword Size = GetEnvironmentVariableW(WideName.c_str(), Buffer, 4096);
    return (Size > 0) ? Common::StringUtils::FromWide(Buffer) : "";
}

bool WindowsPlatform::SetEnvironmentVariable(const Common::String& Name, const Common::String& Value) {
    auto WideName = Common::StringUtils::ToWide(Name);
    auto WideValue = Common::StringUtils::ToWide(Value);
    return ::SetEnvironmentVariableW(WideName.c_str(), WideValue.c_str()) != 0;
}

Common::String WindowsPlatform::GetLastErrorString() {
    wchar_t* Buffer = nullptr;
    // NOTE: FormatMessageW allocates, we must free with LocalFree
    Dword Size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                                nullptr, GetLastError(), 0,
                                reinterpret_cast<wchar_t*>(&Buffer), 0, nullptr);
    Common::String Result = (Buffer) ? Common::StringUtils::FromWide(std::wstring(Buffer, Size)) : "";
    LocalFree(Buffer);
    return Result;
}

Dword WindowsPlatform::GetLastErrorCode() { return ::GetLastError(); }

bool WindowsPlatform::IsWow64() {
    BOOL IsWow = FALSE;
    return IsWow64Process(GetCurrentProcess(), &IsWow) && IsWow;
}

Common::String WindowsPlatform::GetApplicationDataPath() {
    wchar_t Path[MAX_PATH];
    SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, Path);
    return Common::StringUtils::FromWide(Path);
}

Common::String WindowsPlatform::GetTempPath() {
    wchar_t Path[MAX_PATH];
    GetTempPathW(MAX_PATH, Path);
    return Common::StringUtils::FromWide(Path);
}

} // namespace Uues::Core::Platform