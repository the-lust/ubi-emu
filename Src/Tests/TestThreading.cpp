#include "../Core/Threading/ThreadPool.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>
#include <atomic>

namespace Uues::Tests {
using namespace Uues::Core;

bool RunThreadingTests() {
    Log::Logger::GetInstance().Info("[ThreadingTests] Starting");

    int Ok = 0;
    int Total = 0;

    // ThreadPool creation
    Total++;
    {
        Core::Threading::ThreadPool Pool(4);
        if (Pool.GetThreadCount() == 4) Ok++;
        else Log::Logger::GetInstance().Warning("[ThreadingTests] Pool thread count mismatch");
    }

    // ThreadPool with 0 threads (edge case)
    Total++;
    {
        Core::Threading::ThreadPool Pool(0);
        if (Pool.GetThreadCount() == 0) Ok++;
    }

    // simple task enqueue (no crash)
    Total++;
    {
        Core::Threading::ThreadPool Pool(2);
        std::atomic<int> Counter{0};
        Pool.Enqueue([&] { Counter++; });
        Pool.Enqueue([&] { Counter++; });
        Pool.WaitAll();
        if (Counter == 2) Ok++;
        else Log::Logger::GetInstance().Warning("[ThreadingTests] Counter=" +
            std::to_string(Counter.load()) + " (expected 2)");
    }

    printf("[Threading] %d/%d passed\n", Ok, Total);
    return Ok == Total;
}

} // namespace Uues::Tests