#pragma once

#include <mutex>

namespace Uues::Core::Threading {

class CriticalSection {
public:
    void Lock();
    void Unlock();
    bool TryLock();

private:
    std::mutex mMutex;
};

class ScopedLock {
public:
    explicit ScopedLock(CriticalSection& Section) : mSection(Section) { mSection.Lock(); }
    ~ScopedLock() { mSection.Unlock(); }
    ScopedLock(const ScopedLock&) = delete;
    ScopedLock& operator=(const ScopedLock&) = delete;

private:
    CriticalSection& mSection;
};

} // namespace Uues::Core::Threading