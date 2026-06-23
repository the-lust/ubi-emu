#include "ProtobufSerializer.hpp"

namespace Uues::Core::Proto {

Common::ByteArray ProtobufSerializer::EncodeVarint(uint64_t Value) {
    // wire format: base-128 varint, MSB indicates continuation
    Common::ByteArray Result;
    while (Value > 0x7F) {
        Result.push_back(static_cast<Byte>((Value & 0x7F) | 0x80));
        Value >>= 7;
    }
    Result.push_back(static_cast<Byte>(Value));
    return Result;
}

Common::ByteArray ProtobufSerializer::EncodeTag(int FieldNumber, ProtoFieldType Type) {
    uint64_t Tag = (static_cast<uint64_t>(FieldNumber) << 3) | static_cast<uint64_t>(Type);
    return EncodeVarint(Tag);
}

Common::ByteArray ProtobufSerializer::SerializeField(const ProtoField& Field) {
    auto Tag = EncodeTag(Field.GetFieldNumber(), Field.GetFieldType());
    Common::ByteArray Result = Tag;

    switch (Field.GetFieldType()) {
        case ProtoFieldType::Varint: {
            auto Val = std::get<int64_t>(Field.GetValue());
            auto Varint = EncodeVarint(static_cast<uint64_t>(Val));
            Result.insert(Result.end(), Varint.begin(), Varint.end());
            break;
        }
        case ProtoFieldType::Fixed64: {
            auto Val = static_cast<uint64_t>(std::get<int64_t>(Field.GetValue()));
            for (int I = 0; I < 8; ++I) {
                Result.push_back(static_cast<Byte>((Val >> (I * 8)) & 0xFF));
            }
            break;
        }
        case ProtoFieldType::LengthDelimited: {
            auto Bytes = std::get<Common::ByteArray>(Field.GetValue());
            auto Length = EncodeVarint(Bytes.size());
            Result.insert(Result.end(), Length.begin(), Length.end());
            Result.insert(Result.end(), Bytes.begin(), Bytes.end());
            break;
        }
        case ProtoFieldType::Fixed32: {
            auto Val = static_cast<uint32_t>(std::get<int64_t>(Field.GetValue()));
            for (int I = 0; I < 4; ++I) {
                Result.push_back(static_cast<Byte>((Val >> (I * 8)) & 0xFF));
            }
            break;
        }
    }
    return Result;
}

Common::ByteArray ProtobufSerializer::SerializeMessage(const std::vector<ProtoField>& Fields) {
    Common::ByteArray Result;
    for (const auto& Field : Fields) {
        auto Serialized = SerializeField(Field);
        Result.insert(Result.end(), Serialized.begin(), Serialized.end());
    }
    // TODO: sort fields by field number (protobuf wire format doesn't require it but convention does)
    return Result;
}

} // namespace Uues::Core::Proto