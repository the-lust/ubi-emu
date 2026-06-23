#include "Logger.hpp"
#include "../Common/StringUtils.hpp"
#include "ConsoleTarget.hpp"
#include <iostream>

namespace Uues::Core::Log {

Logger& Logger::GetInstance() {
    static Logger Instance;
    return Instance;
}

Logger::~Logger() = default;

void Logger::AddTarget(std::unique_ptr<LogTarget> Target) {
    mTargets.push_back(std::move(Target));
}

void Logger::RemoveAllTargets() { mTargets.clear(); }

void Logger::SetLevel(LogLevel Level) { mLevel = Level; }

void Logger::Trace(const Common::String& Message) {
    // debug spam, skip level check for performance in hot paths? nah
    Log(LogLevel::Trace, Message);
}
void Logger::Debug(const Common::String& Message) { Log(LogLevel::Debug, Message); }
void Logger::Info(const Common::String& Message) { Log(LogLevel::Info, Message); }
void Logger::Warning(const Common::String& msg) { Log(LogLevel::Warning, msg); }
void Logger::Error(const Common::String& Message) { Log(LogLevel::Error, Message); }
void Logger::Fatal(const Common::String& Message) { Log(LogLevel::Fatal, Message); }

void Logger::Log(LogLevel Level, const Common::String& Message) {
    // NOTE: some targets do their own level check, some rely on this --
    // should we just always forward and let targets decide?
    if (Level < mLevel) return;

    static const char* LevelNames[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "NONE"};
    auto LevelIdx = static_cast<size_t>(Level);
    auto LevelName = (LevelIdx < 7) ? LevelNames[LevelIdx] : "UNKNOWN";

    auto Formatted = Common::StringUtils::Format("[%s] %s", LevelName, Message.c_str());

    for (auto& Target : mTargets) {
        // FIXME: if a target returns false from IsEnabled, we still call Write and it double-checks
        Target->Write(Level, Formatted);
    }
}

} // namespace Uues::Core::Log