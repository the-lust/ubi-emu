#pragma once

#include "../Common/Types.hpp"
#include <windows.h>

namespace Uues::Core::Memory {

class MemoryAllocator {
public:
    static void* Allocate(size_t Size, Dword Protection = PAGE_EXECUTE_READWRITE);
    static void* AllocateNear(size_t Size, void* NearAddress, size_t MaxDistance = 0x7FFFFFFF);
    static bool Free(void* Address);
    static bool Protect(void* Address, size_t Size, Dword NewProtection, Dword* OldProtection = nullptr);
    static size_t GetPageSize();

private:
    MemoryAllocator() = delete;
};

} // namespace Uues::Core::Memory