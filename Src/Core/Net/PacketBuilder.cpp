#include "PacketBuilder.hpp"

namespace Uues::Core::Net {

PacketBuilder::PacketBuilder() {}
PacketBuilder::~PacketBuilder() = default;

void PacketBuilder::WriteByte(Byte V) { mBuffer.push_back(V); }
void PacketBuilder::WriteWord(Word V) {
    mBuffer.insert(mBuffer.end(), {static_cast<Byte>(V & 0xFF), static_cast<Byte>((V >> 8) & 0xFF)});
}
void PacketBuilder::WriteDword(Dword V) {
    // little-endian always, no endianness check
    mBuffer.insert(mBuffer.end(), {static_cast<Byte>(V & 0xFF), static_cast<Byte>((V >> 8) & 0xFF), static_cast<Byte>((V >> 16) & 0xFF), static_cast<Byte>((V >> 24) & 0xFF)});
}
void PacketBuilder::WriteQword(Qword V) {
    for (int I = 0; I < 8; ++I) {
        mBuffer.push_back(static_cast<Byte>((V >> (I * 8)) & 0xFF));
    }
}
void PacketBuilder::WriteBytes(const Common::ByteArray& Data) { mBuffer.insert(mBuffer.end(), Data.begin(), Data.end()); }
void PacketBuilder::WriteString(const Common::String& Str) {
    WriteDword(static_cast<Dword>(Str.size()));
    mBuffer.insert(mBuffer.end(), Str.begin(), Str.end());
}
void PacketBuilder::WriteRaw(const void* Data, size_t Size) {
    auto Bytes = static_cast<const Byte*>(Data);
    mBuffer.insert(mBuffer.end(), Bytes, Bytes + Size);
}

Common::ByteArray PacketBuilder::Build() const { return mBuffer; }
size_t PacketBuilder::GetSize() const { return mBuffer.size(); }
void PacketBuilder::Clear() { mBuffer.clear(); }

} // namespace Uues::Core::Net