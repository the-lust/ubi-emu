#pragma once

#include "../Common/Types.hpp"
#include "ProtoField.hpp"
#include <vector>

namespace Uues::Core::Proto {

class ProtobufSerializer {
public:
    static Common::ByteArray SerializeMessage(const std::vector<ProtoField>& Fields);
    static Common::ByteArray SerializeField(const ProtoField& Field);

private:
    static Common::ByteArray EncodeVarint(uint64_t Value);
    static Common::ByteArray EncodeTag(int FieldNumber, ProtoFieldType Type);
};

} // namespace Uues::Core::Proto