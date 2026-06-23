#include "TrampolineAllocator.hpp"
#include <windows.h>

namespace Uues::Core::Hook {

TrampolineAllocator& TrampolineAllocator::GetInstance() {
    static TrampolineAllocator Instance;
    return Instance;
}

TrampolineAllocator::~TrampolineAllocator() {
    FreeAll();
}

void* TrampolineAllocator::Allocate(size_t Size) {
    void* Address = VirtualAlloc(nullptr, Size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (Address) {
        mAllocations.push_back({Address, Size});
    }
    return Address;
}

void TrampolineAllocator::Free(void* Address) {
    auto It = std::find_if(mAllocations.begin(), mAllocations.end(),
        [Address](const Allocation& A) { return A.Address == Address; });
    if (It != mAllocations.end()) {
        VirtualFree(It->Address, 0, MEM_RELEASE);
        mAllocations.erase(It);
    }
}

void TrampolineAllocator::FreeAll() {
    for (auto& Alloc : mAllocations) {
        VirtualFree(Alloc.Address, 0, MEM_RELEASE);
    }
    mAllocations.clear();
    // TODO: consider whether we should re-enable MinHook after freeing
}

} // namespace Uues::Core::Hook