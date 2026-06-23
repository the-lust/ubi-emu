#include "BufferUtils.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace Uues::Core::Common {

ByteArray BufferUtils::FromHex(const String& Hex) {
    ByteArray Result;
    String Clean;
    for (char C : Hex) {
        if (std::isxdigit(static_cast<unsigned char>(C))) Clean += C;
    }
    // HACK: odd-length hex strings just return empty, maybe we should pad with leading 0?
    if (Clean.length() % 2 != 0) return Result;
    Result.resize(Clean.length() / 2);
    for (size_t I = 0; I < Result.size(); ++I) {
        std::string ByteStr = Clean.substr(I * 2, 2);
        Result[I] = static_cast<Byte>(std::stoul(ByteStr, nullptr, 16));
    }
    return Result;
}

String BufferUtils::ToHex(const ByteArray& Data) {
    std::ostringstream Oss;
    Oss << std::hex << std::setfill('0');
    for (Byte B : Data) {
        Oss << std::setw(2) << static_cast<int>(B);
    }
    return Oss.str();
}

ByteArray BufferUtils::Concatenate(const ByteArray& A, const ByteArray& B) {
    ByteArray Result;
    Result.reserve(A.size() + B.size());
    Result.insert(Result.end(), A.begin(), A.end());
    Result.insert(Result.end(), B.begin(), B.end());
    return Result;
}

ByteArray BufferUtils::SubBuffer(const ByteArray& Data, size_t Offset, size_t Length) {
    if (Offset >= Data.size()) return {};
    size_t ActualLength = std::min(Length, Data.size() - Offset);
    return {Data.begin() + Offset, Data.begin() + Offset + ActualLength};
}

bool BufferUtils::Compare(const ByteArray& A, const ByteArray& B) {
    return A.size() == B.size() && std::equal(A.begin(), A.end(), B.begin());
}

void BufferUtils::ZeroMemory(Byte* Buffer, size_t Size) {
    if (Buffer) std::memset(Buffer, 0, Size);
}

void BufferUtils::CopyMemory(Byte* Dest, const Byte* Src, size_t Size) {
    if (Dest && Src) std::memcpy(Dest, Src, Size);
}

} // namespace Uues::Core::Common