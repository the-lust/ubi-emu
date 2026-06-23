#include "TimeUtils.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace Uues::Core::Common {

int64_t TimeUtils::GetCurrentTimestamp() {
    // epoch = unix timestamp (seconds since 1970)
    return std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

String TimeUtils::FormatTimestamp(int64_t Ts) {
    std::time_t Time = static_cast<std::time_t>(Ts);
    std::tm Tm;
#ifdef _WIN32
    localtime_s(&Tm, &Time);
#else
    localtime_r(&Time, &Tm);
#endif
    std::ostringstream Oss;
    Oss << std::put_time(&Tm, "%Y-%m-%d %H:%M:%S");
    return Oss.str();
}

String TimeUtils::GetCurrentDateTimeString() {
    return FormatTimestamp(GetCurrentTimestamp());
}

void TimeUtils::SleepMs(Dword Ms) {
#ifdef _WIN32
    ::Sleep(Ms);
#else
    usleep(Ms * 1000);
#endif
}

int64_t TimeUtils::MeasureElapsedMs(int64_t Start) {
    auto Now = std::chrono::steady_clock::now();
    auto StartTime = std::chrono::steady_clock::time_point(
        std::chrono::steady_clock::duration(Start)
    );
    return std::chrono::duration_cast<std::chrono::milliseconds>(Now - StartTime).count();
}

} // namespace Uues::Core::Common