#include "LogTarget.hpp"

namespace Uues::Core::Log {

bool LogTarget::IsEnabled(LogLevel Level) const {
    // HACK: this is inverted from what you'd expect -- higher enum value = less verbose
    return Level >= mMinLevel;
}

void LogTarget::SetLevel(LogLevel Level) {
    mMinLevel = Level;
}

} // namespace Uues::Core::Log