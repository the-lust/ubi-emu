#include "ProtoField.hpp"

namespace Uues::Core::Proto {

ProtoField::ProtoField(int FieldNumber, ProtoFieldType Type)
    : mFieldNumber(FieldNumber), mFieldType(Type), mValue(int64_t(0)) {
        // TODO: validate FieldNumber > 0 (protobuf convention)
}

ProtoField::ProtoField(int FieldNumber, ProtoFieldType Type, FieldValue Value)
    : mFieldNumber(FieldNumber), mFieldType(Type), mValue(Value) {}

int ProtoField::GetFieldNumber() const { return mFieldNumber; }
ProtoFieldType ProtoField::GetFieldType() const { return mFieldType; }
ProtoField::FieldValue ProtoField::GetValue() const { return mValue; }

} // namespace Uues::Core::Proto