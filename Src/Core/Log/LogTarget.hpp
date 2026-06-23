#pragma once

#include "../Common/Types.hpp"
#include "LogLevel.hpp"

namespace Uues::Core::Log {

class LogTarget {
public:
    virtual ~LogTarget() = default;
    virtual void Write(LogLevel Level, const Common::String& Message) = 0;
    virtual void Flush() = 0;
    virtual bool IsEnabled(LogLevel Level) const;
    void SetLevel(LogLevel Level);

protected:
    LogLevel mMinLevel = LogLevel::Debug;
};

} // namespace Uues::Core::Log