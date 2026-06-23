#include "../Core/Memory/MemoryPatcher.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>
#include <cstdint>

namespace Uues::Tests {

bool RunMemoryTests() {
    Log::Logger::GetInstance().Info("[MemoryTests] Starting memory tests");

    int Errors = 0;

    // MemoryPatcher basic life cycle
    {
        Core::Memory::MemoryPatcher Patcher;
        if (!Patcher.IsInitialized()) {
            Log::Logger::GetInstance().Info("[MemoryTests] Patcher uninitialized as expected");
        } else {
            Errors++;
        }
    }

    // try applying an empty patch (should do nothing)
    {
        Core::Memory::MemoryPatcher Patcher;
        bool Ok = Patcher.ApplyPatch({}); // empty patch
        if (!Ok) {
            Log::Logger::GetInstance().Warning("[MemoryTests] Empty patch rejected (fine)");
        }
    }

    printf("[Memory] Memory patcher tests: %s\n", Errors == 0 ? "PASS" : "FAIL");
    return Errors == 0;
}

} // namespace Uues::Tests