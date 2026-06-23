#include "CriticalSection.hpp"

namespace Uues::Core::Threading {

void CriticalSection::Lock() {
    // TODO: add deadlock detection (track thread ID, detect re-entrant locks)
    mMutex.lock();
}
void CriticalSection::Unlock() { mMutex.unlock(); }
bool CriticalSection::TryLock() { return mMutex.try_lock(); }

} // namespace Uues::Core::Threading