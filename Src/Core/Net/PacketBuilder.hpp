#pragma once

#include "../Common/Types.hpp"
#include <cstring>

namespace Uues::Core::Net {

class PacketBuilder {
public:
    PacketBuilder();
    ~PacketBuilder();

    void WriteByte(Byte Value);
    void WriteWord(Word Value);
    void WriteDword(Dword Value);
    void WriteQword(Qword Value);
    void WriteBytes(const Common::ByteArray& Data);
    void WriteString(const Common::String& Str);
    void WriteRaw(const void* Data, size_t Size);

    Common::ByteArray Build() const;
    size_t GetSize() const;
    void Clear();

private:
    Common::ByteArray mBuffer;
};

} // namespace Uues::Core::Net