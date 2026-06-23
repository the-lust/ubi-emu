#pragma once

#include <string>

namespace Uues::Core::Ini {

enum class IniType {
    Section,
    KeyValue,
    Comment,
    Blank,
    Invalid
};

} // namespace Uues::Core::Ini