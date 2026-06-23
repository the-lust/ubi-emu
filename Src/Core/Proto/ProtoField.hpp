#pragma once

#include "../Common/Types.hpp"
#include <variant>

namespace Uues::Core::Proto {

enum class ProtoFieldType {
    Varint,
    Fixed64,
    LengthDelimited,
    Fixed32
};

class ProtoField {
public:
    using FieldValue = std::variant<int64_t, uint64_t, double, float, Common::ByteArray, Common::String>;

    ProtoField(int FieldNumber, ProtoFieldType Type);
    ProtoField(int FieldNumber, ProtoFieldType Type, FieldValue Value);

    int GetFieldNumber() const;
    ProtoFieldType GetFieldType() const;
    FieldValue GetValue() const;

    template<typename T>
    T GetAs() const { return std::get<T>(mValue); }

private:
    int mFieldNumber;
    ProtoFieldType mFieldType;
    FieldValue mValue;
};

} // namespace Uues::Core::Proto