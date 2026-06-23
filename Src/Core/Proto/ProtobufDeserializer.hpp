#pragma once

#include "../Common/Types.hpp"
#include "ProtoField.hpp"
#include <vector>

namespace Uues::Core::Proto {

class ProtobufDeserializer {
public:
    static std::vector<ProtoField> DeserializeMessage(const Common::ByteArray& Data);

private:
    static uint64_t DecodeVarint(const Common::ByteArray& Data, size_t& Offset);
    static ProtoFieldType DecodeType(uint64_t Tag);
    static int DecodeFieldNumber(uint64_t Tag);
};

} // namespace Uues::Core::Proto