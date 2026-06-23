#pragma once

#include "../Common/Types.hpp"
#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>

namespace Uues::Core::Threading {

class ThreadPool {
public:
    explicit ThreadPool(size_t ThreadCount = 0);
    ~ThreadPool();

    void Enqueue(std::function<void()> Task);
    void WaitAll();
    size_t GetThreadCount() const;
    void SetMaxThreads(size_t Count);

private:
    std::vector<std::thread> mWorkers;
    std::queue<std::function<void()>> mTasks;
    std::mutex mMutex;
    std::condition_variable mCondition;
    std::atomic<bool> mStop{false};
    void WorkerLoop();
};

} // namespace Uues::Core::Threading