#include "PacketParser.hpp"
#include "../Common/Errors.hpp"
#include <stdexcept>

namespace Uues::Core::Net {

PacketParser::PacketParser(const Common::ByteArray& Data) : mData(Data) {}

Byte PacketParser::ReadByte() {
    if (mPosition + 1 > mData.size()) throw std::out_of_range("PacketParser: ReadByte overflow");
    return mData[mPosition++];
}

Word PacketParser::ReadWord() {
    if (mPosition + 2 > mData.size()) {
        throw std::out_of_range("PacketParser: ReadWord overflow");
    }
    Word V = mData[mPosition] | (static_cast<Word>(mData[mPosition + 1]) << 8);
    mPosition += 2;
    return V;
}

Dword PacketParser::ReadDword() {
    if (mPosition + 4 > mData.size()) throw std::out_of_range("PacketParser: ReadDword overflow");
    Dword V = mData[mPosition] | (static_cast<Dword>(mData[mPosition + 1]) << 8) |
              (static_cast<Dword>(mData[mPosition + 2]) << 16) | (static_cast<Dword>(mData[mPosition + 3]) << 24);
    mPosition += 4;
    return V;
}

Qword PacketParser::ReadQword() {
    Qword V = 0;
    for (int I = 0; I < 8; ++I) {
        V |= static_cast<Qword>(ReadByte()) << (I * 8);
    }
    return V;
}

Common::ByteArray PacketParser::ReadBytes(size_t Count) {
    if (mPosition + Count > mData.size()) throw std::out_of_range("PacketParser: ReadBytes overflow");
    auto Result = Common::ByteArray(mData.begin() + mPosition, mData.begin() + mPosition + Count);
    mPosition += Count;
    return Result;
}

Common::String PacketParser::ReadString() {
    auto Length = ReadDword();
    auto Bytes = ReadBytes(Length);
    return Common::String(Bytes.begin(), Bytes.end());
}

void PacketParser::Skip(size_t Count) { mPosition += Count; }
size_t PacketParser::GetRemaining() const { return mData.size() - mPosition; }
bool PacketParser::HasMore() const { return mPosition < mData.size(); }
size_t PacketParser::GetPosition() const { return mPosition; }

} // namespace Uues::Core::Net