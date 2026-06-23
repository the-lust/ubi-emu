#include "ArchitectureDetector.hpp"
#include <windows.h>

namespace Uues::Core::Platform {

Architecture ArchitectureDetector::GetCurrentArchitecture() {
#ifdef _WIN64
    return Architecture::X64;
#elif _WIN32
    BOOL IsWow = FALSE;
    if (::IsWow64Process(GetCurrentProcess(), &IsWow) && IsWow) {
        return Architecture::X64;
    }
    return Architecture::X86;
#else
    return Architecture::Unknown;
#endif
}

bool ArchitectureDetector::IsX86() { return GetCurrentArchitecture() == Architecture::X86; }
bool ArchitectureDetector::IsX64() { return GetCurrentArchitecture() == Architecture::X64; }

bool ArchitectureDetector::IsWow64Process() {
    BOOL IsWow = FALSE;
    // NOTE: IsWow64Process2 exists on Win10+ but we use the original for compatibility
    return ::IsWow64Process(GetCurrentProcess(), &IsWow) && IsWow;
}

Common::String ArchitectureDetector::GetArchitectureString() {
    switch (GetCurrentArchitecture()) {
        case Architecture::X86:   return "x86";
        case Architecture::X64:   return "x64";
        case Architecture::Arm64: return "arm64";
        default:                  return "unknown";
    }
}

} // namespace Uues::Core::Platform