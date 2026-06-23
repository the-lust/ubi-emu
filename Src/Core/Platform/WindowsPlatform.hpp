#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Platform {

class WindowsPlatform {
public:
    static Common::String GetModulePath(HMODULE Module = nullptr);
    static Common::String GetSystemDirectory();
    static Common::String GetEnvironmentVariable(const Common::String& Name);
    static bool SetEnvironmentVariable(const Common::String& Name, const Common::String& Value);
    static Common::String GetLastErrorString();
    static Dword GetLastErrorCode();
    static bool IsWow64();
    static Common::String GetApplicationDataPath();
    static Common::String GetTempPath();

private:
    WindowsPlatform() = delete;
};

} // namespace Uues::Core::Platform