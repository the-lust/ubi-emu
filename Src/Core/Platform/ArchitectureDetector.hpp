#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Platform {

enum class Architecture {
    X86,
    X64,
    Arm64,
    Unknown
};

class ArchitectureDetector {
public:
    static Architecture GetCurrentArchitecture();
    static bool IsX86();
    static bool IsX64();
    static bool IsWow64Process();
    static Common::String GetArchitectureString();

private:
    ArchitectureDetector() = delete;
};

} // namespace Uues::Core::Platform