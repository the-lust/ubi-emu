#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Memory {

class MemoryPatcher {
public:
    static bool PatchBytes(void* Address, const Common::ByteArray& Bytes);
    static bool PatchBytes(uintptr_t Address, const Common::ByteArray& Bytes);
    static bool PatchByte(void* Address, Byte Value);
    static bool PatchWord(void* Address, Word Value);
    static bool PatchDword(void* Address, Dword Value);
    static bool NopBytes(void* Address, size_t Count);
    static bool WriteJump(void* From, void* To);
    static bool WriteCall(void* From, void* To);
    static Common::ByteArray ReadBytes(void* Address, size_t Count);
    static bool RestoreBytes(void* Address, const Common::ByteArray& Original);

private:
    MemoryPatcher() = delete;
};

} // namespace Uues::Core::Memory