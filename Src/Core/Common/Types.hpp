#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <memory>

namespace Uues::Core::Common {

using Byte = uint8_t;
using Word = uint16_t;
using Dword = uint32_t;
using Qword = uint64_t;

using ByteArray = std::vector<Byte>;
using ByteSpan = std::span<const Byte>;

using String = std::string;
using WString = std::wstring;
using StringList = std::vector<String>;

using Guid = std::array<Byte, 16>;

struct Version {
    Dword Major;
    Dword Minor;
    Dword Patch;
    Dword Build;
};

struct Range {
    uintptr_t Start;
    uintptr_t End;
};

} // namespace Uues::Core::Common