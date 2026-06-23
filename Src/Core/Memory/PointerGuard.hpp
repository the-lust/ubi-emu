#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Memory {

template<typename T>
class PointerGuard {
public:
    explicit PointerGuard(T* Pointer) : mPointer(Pointer) {}
    ~PointerGuard() {
        if (mPointer) {
            // HACK: non-owning, but what if someone wants owning semantics?
            mPointer = nullptr;
        }
    }

    PointerGuard(const PointerGuard&) = delete;
    PointerGuard& operator=(const PointerGuard&) = delete;

    PointerGuard(PointerGuard&& Other) noexcept : mPointer(Other.mPointer) {
        Other.mPointer = nullptr;
    }

    PointerGuard& operator=(PointerGuard&& Other) noexcept {
        if (this != &Other) {
            mPointer = Other.mPointer;
            Other.mPointer = nullptr;
        }
        return *this;
    }

    T* Get() const { return mPointer; }
    T* operator->() const { return mPointer; }
    T& operator*() const { return *mPointer; }
    explicit operator bool() const { return mPointer != nullptr; }

private:
    T* mPointer;
};

} // namespace Uues::Core::Memory