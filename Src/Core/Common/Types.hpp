#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <span>

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

} // namespace Uues::Core::Common

// Bring common types into Core namespace for convenient access from sub-namespaces
namespace Uues::Core {
    using Common::Byte;
    using Common::Word;
    using Common::Dword;
    using Common::Qword;
    using Common::ByteArray;
    using Common::ByteSpan;
    using Common::String;
    using Common::WString;
    using Common::StringList;
    using Common::Guid;
}

namespace Uues::Core::Common {

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