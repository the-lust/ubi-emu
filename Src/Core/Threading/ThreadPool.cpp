#include "ThreadPool.hpp"
#include <algorithm>

namespace Uues::Core::Threading {

ThreadPool::ThreadPool(size_t ThreadCount) {
    if (ThreadCount == 0) ThreadCount = std::thread::hardware_concurrency();
    if (ThreadCount == 0) ThreadCount = 4;
    for (size_t I = 0; I < ThreadCount; ++I) {
        mWorkers.emplace_back(&ThreadPool::WorkerLoop, this);
    }
}

ThreadPool::~ThreadPool() {
    mStop = true;
    mCondition.notify_all();
    for (auto& Worker : mWorkers) {
        if (Worker.joinable()) Worker.join();
    }
}

void ThreadPool::Enqueue(std::function<void()> Task) {
    {
        std::lock_guard<std::mutex> Lock(mMutex);
        mTasks.push(std::move(Task));
    }
    // NOTE: notify_one wakes one worker, if all workers are busy, task stays queued
    mCondition.notify_one();
}

void ThreadPool::WaitAll() {
    while (true) {
        std::unique_lock<std::mutex> Lock(mMutex);
        if (mTasks.empty()) break;
        Lock.unlock();
        std::this_thread::yield();  // busy-wait, not ideal but works
    }
    // HACK: this doesn't wait for in-flight tasks, only the queue
}

size_t ThreadPool::GetThreadCount() const { return mWorkers.size(); }

void ThreadPool::SetMaxThreads(size_t Count) {
    // Changing thread count at runtime is not supported in this implementation.
    (void)Count;
}

void ThreadPool::WorkerLoop() {
    while (true) {
        std::function<void()> Task;
        {
            std::unique_lock<std::mutex> Lock(mMutex);
            mCondition.wait(Lock, [this] { return mStop || !mTasks.empty(); });
            if (mStop && mTasks.empty()) return;
            Task = std::move(mTasks.front());
            mTasks.pop();
        }
        Task();
    }
}

} // namespace Uues::Core::Threading