#pragma once

#include <condition_variable>
#include <mutex>
#include <chrono>

namespace Uues::Core::Threading {

class EventSignal {
public:
    EventSignal();
    ~EventSignal();

    void Signal();
    void Wait();
    bool WaitFor(int TimeoutMs);
    void Reset();

private:
    std::mutex mMutex;
    std::condition_variable mCondition;
    bool mSignaled;
};

} // namespace Uues::Core::Threading