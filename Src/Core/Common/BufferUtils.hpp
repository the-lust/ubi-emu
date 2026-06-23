#pragma once

#include "Types.hpp"
#include <cstring>

namespace Uues::Core::Common {

class BufferUtils {
public:
    static ByteArray FromHex(const String& Hex);
    static String ToHex(const ByteArray& Data);
    static ByteArray Concatenate(const ByteArray& A, const ByteArray& B);
    static ByteArray SubBuffer(const ByteArray& Data, size_t Offset, size_t Length);
    static bool Compare(const ByteArray& A, const ByteArray& B);
    static void ZeroMemory(Byte* Buffer, size_t Size);
    static void CopyMemory(Byte* Dest, const Byte* Src, size_t Size);

private:
    BufferUtils() = delete;
};

} // namespace Uues::Core::Common