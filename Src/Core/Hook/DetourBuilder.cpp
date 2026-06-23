#include "DetourBuilder.hpp"
#include <cstring>

namespace Uues::Core::Hook {

DetourBuilder::DetourBuilder() {}
DetourBuilder::~DetourBuilder() = default;

void* DetourBuilder::BuildDetour(void* TargetFunction, const Common::ByteArray& DetourCode) {
    mDetourCode = DetourCode;
    return TargetFunction;
}

bool DetourBuilder::IsValidDetour(void* Address, size_t MinLength) const {
    auto Bytes = static_cast<Byte*>(Address);
    for (size_t I = 0; I < MinLength; ++I) {
        if (Bytes[I] == 0xCC) return false;
        if (Bytes[I] == 0xE9) return false;
    }
    return true;
}

size_t DetourBuilder::GetNecessaryLength(void* TargetFunction, size_t MinLength) const {
    auto Bytes = static_cast<Byte*>(TargetFunction);
    size_t Length = 0;
    while (Length < MinLength) {
        Byte Opcode = Bytes[Length];
        Length += 1;
        // opcode lengths for x86, enough for most common detour targets
        if (Opcode == 0xE9) Length += 4;     // jmp rel32
        else if (Opcode >= 0xE8) Length += 4; // call rel32
        else if (Opcode >= 0xB8 && Opcode <= 0xBF) Length += 4; // mov reg, imm32
        else if (Opcode == 0x66) continue;    // operand size prefix
        else if (Opcode >= 0x50 && Opcode <= 0x57) continue; // push reg
        else if (Opcode >= 0xA0 && Opcode <= 0xA3) Length += 4;
        else if (Opcode == 0x68) Length += 4; // push imm32
        else if (Opcode == 0x6A) Length += 1; // push imm8
        else if (Opcode == 0xC7) Length += 6; // mov r/m, imm32
        else if (Opcode >= 0x74 && Opcode <= 0x7F) Length += 1; // jcc rel8
        else if (Opcode >= 0x70 && Opcode <= 0x7F) Length += 1; // jcc rel8
        else if (Opcode == 0xEB) Length += 1; // jmp rel8
        else if (Opcode == 0xFF) Length += 1; // opcode group with ModRM
    }
    return Length;
}

} // namespace Uues::Core::Hook