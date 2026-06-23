#include "DebugOutputTarget.hpp"
#include <windows.h>

namespace Uues::Core::Log {

void DebugOutputTarget::Write(LogLevel Level, const Common::String& Message) {
    if (!IsEnabled(Level)) {
        return;
    }
    // OutputDebugStringA is slow for high-frequency logging
    OutputDebugStringA(Message.c_str());
    OutputDebugStringA("\n");
}

void DebugOutputTarget::Flush() {}

} // namespace Uues::Core::Log