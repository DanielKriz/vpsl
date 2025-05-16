#include <vp/resources/thread_pool.hpp>

#include <spdlog/spdlog.h>

namespace vp {

ThreadPool::ThreadPool(u32 threadCount) {
    spdlog::debug("initializing thread pool with {} threads", threadCount);
    m_threads.reserve(threadCount);
    for (u32 i = 0u; i < threadCount; ++i) {
        m_threads.emplace_back(&ThreadPool::threadLoop, this);
    }
}

void ThreadPool::enqueueJob(const JobType &job) {
    {
        std::unique_lock<std::mutex> lock (m_queueMutex);
        m_jobs.push(job);
    }
    m_mutexCondition.notify_one();
}

void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock (m_queueMutex);
        m_shouldTerminate = true;
    }
    m_mutexCondition.notify_all();
    for (auto & activeThread : m_threads) {
        activeThread.join();
    }
    m_threads.clear();
}

bool ThreadPool::isBusy() const {
    std::unique_lock<std::mutex> lock (m_queueMutex);
    return not m_jobs.empty();
}

void ThreadPool::threadLoop() {
    while (true) {
        JobType job;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_mutexCondition.wait(lock, [this] {
                return not m_jobs.empty() or m_shouldTerminate;
            });

            if (m_shouldTerminate) {
                return;
            }

            job = m_jobs.front();
            m_jobs.pop();
        }
        job();
    }
}

} // namespace vp
