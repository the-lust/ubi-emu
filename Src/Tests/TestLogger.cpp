#include "../Core/Log/Logger.hpp"
#include "../Core/Log/LogLevel.hpp"
#include <cstdio>

namespace Uues::Tests {

bool RunLoggerTests() {
    printf("[Logger] Tests start\n");

    auto& Logger = Core::Log::Logger::GetInstance();

    // verify all log levels work without crashing
    Logger.Trace("[LoggerTest] trace message");
    Logger.Debug("[LoggerTest] debug message");
    Logger.Info("[LoggerTest] info message");
    Logger.Warning("[LoggerTest] warning message");
    Logger.Error("[LoggerTest] error message");

    // change log level and verify it sticks
    Logger.SetLevel(Core::Log::LogLevel::Warning);
    Logger.Info("[LoggerTest] this should be suppressed (info below warning)");
    Logger.Warning("[LoggerTest] this should appear (warning level)");

    // reset back to debug
    Logger.SetLevel(Core::Log::LogLevel::Debug);

    printf("[Logger] All logger tests completed\n");
    return true;
}

} // namespace Uues::Tests