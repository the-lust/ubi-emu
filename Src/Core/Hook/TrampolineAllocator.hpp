#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Hook {

class TrampolineAllocator {
public:
    static TrampolineAllocator& GetInstance();

    void* Allocate(size_t Size);
    void Free(void* Address);
    void FreeAll();

private:
    TrampolineAllocator() = default;
    ~TrampolineAllocator();
    TrampolineAllocator(const TrampolineAllocator&) = delete;

    struct Allocation { void* Address; size_t Size; };
    std::vector<Allocation> mAllocations;
};

} // namespace Uues::Core::Hook