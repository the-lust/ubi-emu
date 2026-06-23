#include "EventSignal.hpp"

namespace Uues::Core::Threading {

EventSignal::EventSignal() : mSignaled(false) {}
EventSignal::~EventSignal() = default;

void EventSignal::Signal() {
    {
        std::lock_guard<std::mutex> Lock(mMutex);
        mSignaled = true;
    }
    mCondition.notify_one();
}

void EventSignal::Wait() {
    std::unique_lock<std::mutex> Lock(mMutex);
    // NOTE: spurious wakeups are handled by the predicate lambda
    mCondition.wait(Lock, [this] { return mSignaled; });
    mSignaled = false;
}

bool EventSignal::WaitFor(int TimeoutMs) {
    std::unique_lock<std::mutex> Lock(mMutex);
    auto Result = mCondition.wait_for(Lock, std::chrono::milliseconds(TimeoutMs),
                                       [this] { return mSignaled; });
    if (Result) mSignaled = false;
    return Result;
}

void EventSignal::Reset() {
    std::lock_guard<std::mutex> Lock(mMutex);
    mSignaled = false;
}

} // namespace Uues::Core::Threading