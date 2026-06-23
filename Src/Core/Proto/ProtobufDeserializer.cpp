#include "ProtobufDeserializer.hpp"

namespace Uues::Core::Proto {

uint64_t ProtobufDeserializer::DecodeVarint(const Common::ByteArray& Data, size_t& Offset) {
    uint64_t Result = 0;
    int Shift = 0;
    while (Offset < Data.size()) {
        Byte B = Data[Offset++];
        Result |= static_cast<uint64_t>(B & 0x7F) << Shift;
        if (!(B & 0x80)) break;
        Shift += 7;
        // HACK: if Shift > 63 we'd overflow, but protobuf varints shouldn't be that long
    }
    return Result;
}

ProtoFieldType ProtobufDeserializer::DecodeType(uint64_t Tag) {
    return static_cast<ProtoFieldType>(Tag & 0x07);
}

int ProtobufDeserializer::DecodeFieldNumber(uint64_t Tag) {
    return static_cast<int>(Tag >> 3);
}

std::vector<ProtoField> ProtobufDeserializer::DeserializeMessage(const Common::ByteArray& Data) {
    std::vector<ProtoField> Fields;
    size_t Offset = 0;

    while (Offset < Data.size()) {
        auto TagVal = DecodeVarint(Data, Offset);
        auto FieldNumber = DecodeFieldNumber(TagVal);
        auto FieldType = DecodeType(TagVal);

        switch (FieldType) {
            case ProtoFieldType::Varint: {
                auto Val = DecodeVarint(Data, Offset);
                Fields.emplace_back(FieldNumber, FieldType, static_cast<int64_t>(Val));
                break;
            }
            case ProtoFieldType::Fixed64: {
                uint64_t Val = 0;
                for (int I = 0; I < 8; ++I) {
                    Val |= static_cast<uint64_t>(Data[Offset++]) << (I * 8);
                }
                Fields.emplace_back(FieldNumber, FieldType, static_cast<int64_t>(Val));
                break;
            }
            case ProtoFieldType::LengthDelimited: {
                auto Length = DecodeVarint(Data, Offset);
                // FIXME: if Length > remaining data, this will crash with out_of_range
                Common::ByteArray Bytes(Data.begin() + Offset, Data.begin() + Offset + Length);
                Offset += Length;
                Fields.emplace_back(FieldNumber, FieldType, Bytes);
                break;
            }
            case ProtoFieldType::Fixed32: {
                uint32_t Val = 0;
                for (int I = 0; I < 4; ++I) {
                    Val |= static_cast<uint32_t>(Data[Offset++]) << (I * 8);
                }
                Fields.emplace_back(FieldNumber, FieldType, static_cast<int64_t>(Val));
                break;
            }
        }
    }

    return Fields;
}

} // namespace Uues::Core::Proto