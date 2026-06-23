#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Net {

class PacketParser {
public:
    explicit PacketParser(const Common::ByteArray& Data);

    Byte ReadByte();
    Word ReadWord();
    Dword ReadDword();
    Qword ReadQword();
    Common::ByteArray ReadBytes(size_t Count);
    Common::String ReadString();
    void Skip(size_t Count);

    size_t GetRemaining() const;
    bool HasMore() const;
    size_t GetPosition() const;

private:
    Common::ByteArray mData;
    size_t mPosition = 0;
};

} // namespace Uues::Core::Net