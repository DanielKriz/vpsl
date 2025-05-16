#ifndef VP_THREAD_POOL_HPP
#define VP_THREAD_POOL_HPP

#include <vp/types.hpp>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

namespace vp {

class ThreadPool {
public:
    explicit ThreadPool(u32 threadCount = std::thread::hardware_concurrency());

    using JobType = std::function<void ()>;
    void enqueueJob(const JobType &job);
    void stop();
    bool isBusy() const;
private:
    void threadLoop();

    bool m_shouldTerminate { false };
    mutable std::mutex m_queueMutex;
    std::condition_variable m_mutexCondition;
    std::vector<std::thread> m_threads;
    std::queue<JobType> m_jobs;
};

} // namespace vp

#endif // VP_THREAD_POOL_HPP
