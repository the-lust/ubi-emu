#pragma once

#include "LogTarget.hpp"

namespace Uues::Core::Log {

class ConsoleTarget : public LogTarget {
public:
    ConsoleTarget();
    ~ConsoleTarget() override;

    void Write(LogLevel Level, const Common::String& Message) override;
    void Flush() override;

    void SetColorEnabled(bool Enabled);

private:
    bool mColorEnabled = true;
    void SetConsoleColor(LogLevel Level);
    void ResetConsoleColor();
};

} // namespace Uues::Core::Log