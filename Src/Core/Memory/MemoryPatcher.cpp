#include "MemoryPatcher.hpp"
#include <windows.h>
#include <cstring>

namespace Uues::Core::Memory {

bool MemoryPatcher::PatchBytes(void* Address, const Common::ByteArray& Bytes) {
    return PatchBytes(reinterpret_cast<uintptr_t>(Address), Bytes);
}

bool MemoryPatcher::PatchBytes(uintptr_t Address, const Common::ByteArray& Bytes) {
    DWORD OldProtect;
    if (!VirtualProtect(reinterpret_cast<void*>(Address), Bytes.size(),
                        PAGE_EXECUTE_READWRITE, &OldProtect)) {
        return false;
    }
    std::memcpy(reinterpret_cast<void*>(Address), Bytes.data(), Bytes.size());
    VirtualProtect(reinterpret_cast<void*>(Address), Bytes.size(), OldProtect, &OldProtect);
    FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(Address), Bytes.size());
    return true;
    // TODO: handle the case where Address isn't page-aligned, VirtualProtect works on pages
}

bool MemoryPatcher::PatchByte(void* Address, Byte Value) {
    return PatchBytes(Address, {Value});
}

bool MemoryPatcher::PatchWord(void* Address, Word Value) {
    Common::ByteArray Bytes = {static_cast<Byte>(Value & 0xFF), static_cast<Byte>((Value >> 8) & 0xFF)};
    return PatchBytes(Address, Bytes);
}

bool MemoryPatcher::PatchDword(void* Address, Dword Value) {
    Common::ByteArray Bytes = {
        static_cast<Byte>(Value & 0xFF),
        static_cast<Byte>((Value >> 8) & 0xFF),
        static_cast<Byte>((Value >> 16) & 0xFF),
        static_cast<Byte>((Value >> 24) & 0xFF)
    };
    return PatchBytes(Address, Bytes);
}

bool MemoryPatcher::NopBytes(void* Address, size_t Count) {
    Common::ByteArray Nops(Count, 0x90);
    return PatchBytes(Address, Nops);
}

bool MemoryPatcher::WriteJump(void* From, void* To) {
    auto FromAddr = reinterpret_cast<uintptr_t>(From);
    auto ToAddr = reinterpret_cast<uintptr_t>(To);
    // FIXME: this truncates 64-bit addresses, relative jump only works within ±2GB
    int32_t Relative = static_cast<int32_t>(ToAddr - FromAddr - 5);
    Common::ByteArray Jump = {0xE9, static_cast<Byte>(Relative & 0xFF),
                              static_cast<Byte>((Relative >> 8) & 0xFF),
                              static_cast<Byte>((Relative >> 16) & 0xFF),
                              static_cast<Byte>((Relative >> 24) & 0xFF)};
    return PatchBytes(From, Jump);
}

bool MemoryPatcher::WriteCall(void* From, void* To) {
    auto FromAddr = reinterpret_cast<uintptr_t>(From);
    auto ToAddr = reinterpret_cast<uintptr_t>(To);
    int32_t Relative = static_cast<int32_t>(ToAddr - FromAddr - 5);
    Common::ByteArray Call = {0xE8, static_cast<Byte>(Relative & 0xFF),
                              static_cast<Byte>((Relative >> 8) & 0xFF),
                              static_cast<Byte>((Relative >> 16) & 0xFF),
                              static_cast<Byte>((Relative >> 24) & 0xFF)};
    return PatchBytes(From, Call);
}

Common::ByteArray MemoryPatcher::ReadBytes(void* Address, size_t Count) {
    Common::ByteArray Result(Count);
    std::memcpy(Result.data(), Address, Count);
    return Result;
}

bool MemoryPatcher::RestoreBytes(void* Address, const Common::ByteArray& Original) {
    return PatchBytes(Address, Original);
}

} // namespace Uues::Core::Memory