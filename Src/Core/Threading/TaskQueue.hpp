#pragma once

#include "../Common/Types.hpp"
#include <queue>
#include <mutex>

namespace Uues::Core::Threading {

template<typename T>
class TaskQueue {
public:
    void Push(T Item) {
        std::lock_guard<std::mutex> Lock(mMutex);
        mQueue.push(std::move(Item));
    }

    bool TryPop(T& Out) {
        std::lock_guard<std::mutex> Lock(mMutex);
        if (mQueue.empty()) return false;
        Out = std::move(mQueue.front());
        mQueue.pop();
        return true;
    }

    bool IsEmpty() const {
        std::lock_guard<std::mutex> Lock(mMutex);
        return mQueue.empty();
    }

    size_t GetSize() const {
        std::lock_guard<std::mutex> Lock(mMutex);
        return mQueue.size();
    }

    void Clear() {
        std::lock_guard<std::mutex> Lock(mMutex);
        while (!mQueue.empty()) mQueue.pop();
    }

private:
    mutable std::mutex mMutex;
    std::queue<T> mQueue;
};

} // namespace Uues::Core::Threading