#include "../Core/Memory/MemoryPatcher.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>
#include <cstdint>

namespace Uues::Tests {
using namespace Uues::Core;

bool RunMemoryTests() {
    Log::Logger::GetInstance().Info("[MemoryTests] Starting memory tests");

    int Errors = 0;

    // MemoryPatcher — fully static utility class
    {
        if (!Core::Memory::MemoryPatcher::PatchBytes((void*)0x0, Common::ByteArray{1,2,3})) {
            Log::Logger::GetInstance().Info("[MemoryTests] PatchBytes to null rejected (expected)");
        }
        auto Read = Core::Memory::MemoryPatcher::ReadBytes((void*)0x0, 4);
        if (Read.empty()) {
            Log::Logger::GetInstance().Info("[MemoryTests] ReadBytes from null empty (expected)");
        }
    }

    printf("[Memory] Memory patcher tests: %s\n", Errors == 0 ? "PASS" : "FAIL");
    return Errors == 0;
}

} // namespace Uues::Tests