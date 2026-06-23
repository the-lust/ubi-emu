#include "ConsoleTarget.hpp"
#include <windows.h>
#include <iostream>

namespace Uues::Core::Log {

ConsoleTarget::ConsoleTarget() {
    // TODO: detect if stdout is redirected and disable colors automatically
}
ConsoleTarget::~ConsoleTarget() = default;

void ConsoleTarget::Write(LogLevel Level, const Common::String& Message) {
    if (!IsEnabled(Level)) {
        return;  // level filtered out
    }
    if (mColorEnabled) SetConsoleColor(Level);
    std::cout << Message << std::endl;
    if (mColorEnabled) ResetConsoleColor();
}

void ConsoleTarget::Flush() {
    std::cout.flush();
}

void ConsoleTarget::SetColorEnabled(bool Enabled) { mColorEnabled = Enabled; }

void ConsoleTarget::SetConsoleColor(LogLevel Level) {
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    switch (Level) {
        case LogLevel::Error:   Color = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
        case LogLevel::Warning: Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
        case LogLevel::Info:    Color = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
        case LogLevel::Debug:   Color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED; break;
        case LogLevel::Trace:   Color = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
        case LogLevel::Fatal:   Color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
        default: break;
    }
    SetConsoleTextAttribute(Console, Color);
}

void ConsoleTarget::ResetConsoleColor() {
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

} // namespace Uues::Core::Log