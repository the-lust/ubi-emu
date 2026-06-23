#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Log {

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
    None
};

} // namespace Uues::Core::Log