#pragma once

#include "../Common/Types.hpp"
#include "LogLevel.hpp"
#include "LogTarget.hpp"
#include <memory>
#include <vector>

namespace Uues::Core::Log {

class Logger {
public:
    static Logger& GetInstance();

    void AddTarget(std::unique_ptr<LogTarget> Target);
    void RemoveAllTargets();
    void SetLevel(LogLevel Level);

    void Trace(const Common::String& Message);
    void Debug(const Common::String& Message);
    void Info(const Common::String& Message);
    void Warning(const Common::String& Message);
    void Error(const Common::String& Message);
    void Fatal(const Common::String& Message);

    void Log(LogLevel Level, const Common::String& Message);

private:
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::vector<std::unique_ptr<LogTarget>> mTargets;
    LogLevel mLevel = LogLevel::Debug;
};

} // namespace Uues::Core::Log