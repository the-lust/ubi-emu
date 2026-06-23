#include "DemuxMessage.hpp"
#include "ProtobufSerializer.hpp"
#include "ProtobufDeserializer.hpp"

namespace Uues::Core::Proto {

DemuxMessage::DemuxMessage() {}
DemuxMessage::~DemuxMessage() = default;

void DemuxMessage::SetRequestId(uint32_t Id) { mRequestId = Id; }
void DemuxMessage::SetServiceId(uint32_t Id) { mServiceId = Id; }
void DemuxMessage::SetMethodId(uint32_t Id) { mMethodId = Id; }
void DemuxMessage::SetPayload(const Common::ByteArray& Payload) { mPayload = Payload; }
void DemuxMessage::SetHeader(const Common::String& Key, const Common::String& Value) { mHeaders[Key] = Value; }

uint32_t DemuxMessage::GetRequestId() const { return mRequestId; }
uint32_t DemuxMessage::GetServiceId() const { return mServiceId; }
uint32_t DemuxMessage::GetMethodId() const { return mMethodId; }
Common::ByteArray DemuxMessage::GetPayload() const { return mPayload; }
Common::String DemuxMessage::GetHeader(const Common::String& Key) const {
    auto It = mHeaders.find(Key);
    return (It != mHeaders.end()) ? It->second : "";
}

Common::ByteArray DemuxMessage::Serialize() const {
    std::vector<ProtoField> Fields;
    Fields.emplace_back(1, ProtoFieldType::Varint, static_cast<int64_t>(mRequestId));
    Fields.emplace_back(2, ProtoFieldType::Varint, static_cast<int64_t>(mServiceId));
    Fields.emplace_back(3, ProtoFieldType::Varint, static_cast<int64_t>(mMethodId));
    Fields.emplace_back(4, ProtoFieldType::LengthDelimited, mPayload);
    return ProtobufSerializer::SerializeMessage(Fields);
}

bool DemuxMessage::Deserialize(const Common::ByteArray& Data) {
    auto Fields = ProtobufDeserializer::DeserializeMessage(Data);
    for (auto& Field : Fields) {
        switch (Field.GetFieldNumber()) {
            case 1: mRequestId = static_cast<uint32_t>(std::get<int64_t>(Field.GetValue())); break;
            case 2: mServiceId = static_cast<uint32_t>(std::get<int64_t>(Field.GetValue())); break;
            case 3: mMethodId = static_cast<uint32_t>(std::get<int64_t>(Field.GetValue())); break;
            case 4: mPayload = std::get<Common::ByteArray>(Field.GetValue()); break;
            default: break;  // unknown fields silently dropped
        }
    }
    return true;
}

} // namespace Uues::Core::Proto