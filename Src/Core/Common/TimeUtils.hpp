#pragma once

#include "Types.hpp"
#include <chrono>

namespace Uues::Core::Common {

class TimeUtils {
public:
    static int64_t GetCurrentTimestamp();
    static String FormatTimestamp(int64_t Timestamp);
    static String GetCurrentDateTimeString();
    static void SleepMs(Dword Milliseconds);
    static int64_t MeasureElapsedMs(int64_t Start);

private:
    TimeUtils() = delete;
};

} // namespace Uues::Core::Common