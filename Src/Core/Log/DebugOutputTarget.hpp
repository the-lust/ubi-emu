#pragma once

#include "LogTarget.hpp"

namespace Uues::Core::Log {

class DebugOutputTarget : public LogTarget {
public:
    void Write(LogLevel Level, const Common::String& Message) override;
    void Flush() override;
};

} // namespace Uues::Core::Log