#pragma once

#include "../Common/Types.hpp"
#include <functional>
#include <vector>

namespace Uues::Core::Memory {

class MemoryScanner {
public:
    MemoryScanner();
    ~MemoryScanner();

    bool Scan(const Common::ByteArray& Pattern, const Common::String& Mask,
              std::vector<uintptr_t>& OutResults);
    bool ScanModule(const Common::String& ModuleName, const Common::ByteArray& Pattern,
                    const Common::String& Mask, std::vector<uintptr_t>& OutResults);
    static uintptr_t FindPattern(const Common::ByteArray& Pattern, const Common::String& Mask,
                                  uintptr_t Start, size_t Size);

    void SetSkipExecutable(bool Skip);

private:
    bool mSkipExecutable = true;
    std::vector<std::pair<uintptr_t, size_t>> GetMemoryRegions();
};

} // namespace Uues::Core::Memory