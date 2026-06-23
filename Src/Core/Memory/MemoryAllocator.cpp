#include "MemoryAllocator.hpp"
#include <windows.h>

namespace Uues::Core::Memory {

void* MemoryAllocator::Allocate(size_t Size, Dword Protection) {
    return VirtualAlloc(nullptr, Size, MEM_COMMIT | MEM_RESERVE, Protection);
}

void* MemoryAllocator::AllocateNear(size_t Size, void* NearAddress, size_t MaxDistance) {
    SYSTEM_INFO SysInfo;
    GetSystemInfo(&SysInfo);
    auto Start = reinterpret_cast<uintptr_t>(NearAddress) - MaxDistance;
    auto End = reinterpret_cast<uintptr_t>(NearAddress) + MaxDistance;
    auto PageStart = Start - (Start % SysInfo.dwAllocationGranularity);

    for (auto Addr = PageStart; Addr < End; Addr += SysInfo.dwAllocationGranularity) {
        MEMORY_BASIC_INFORMATION Mbi;
        if (VirtualQuery(reinterpret_cast<void*>(Addr), &Mbi, sizeof(Mbi)) == sizeof(Mbi)) {
            // NOTE: page alignment is critical, VirtualAlloc rounds to allocation granularity
            if (Mbi.State == MEM_FREE && Mbi.RegionSize >= Size) {
                auto Result = VirtualAlloc(reinterpret_cast<void*>(Addr), Size,
                                            MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
                if (Result) return Result;
            }
        }
    }
    return nullptr;
}

bool MemoryAllocator::Free(void* Address) {
    return VirtualFree(Address, 0, MEM_RELEASE) != 0;
}

bool MemoryAllocator::Protect(void* Address, size_t Size, Dword NewProtection, Dword* OldProtection) {
    DWORD Old;
    bool Result = VirtualProtect(Address, Size, NewProtection, &Old) != 0;
    if (OldProtection) *OldProtection = Old;
    return Result;
}

size_t MemoryAllocator::GetPageSize() {
    SYSTEM_INFO SysInfo;
    GetSystemInfo(&SysInfo);
    return SysInfo.dwPageSize;
}

} // namespace Uues::Core::Memory