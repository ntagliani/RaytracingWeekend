#include "TaskManager.h"
#include "ThreadName.h"
#include <algorithm>
#include <thread>

namespace
{
constexpr uint32_t K = 3;
} // namespace

TaskManager::TaskManager()
{
    m_startingQueue = 0;

    for (uint32_t i = 0; i < k_concurrency; ++i)
    {
        m_executors.emplace_back([this, i]() { run(i); });
        std::this_thread::yield();
    }
}

void TaskManager::run(uint32_t thread_id)
{
    char buffer[64];
    snprintf(buffer, 64, "JobThread: %d", thread_id);
    setThreadName(buffer);

    while (m_run)
    {
        std::function<void()> task;
        for (uint32_t i = 0; i < m_executors.size() + K * k_concurrency; ++i)
        {
            if (m_queues.at((thread_id + i) % k_concurrency).tryPop(task))
                break;
        }
        if (!task && !m_queues.at(thread_id).pop(task))
            break;
        task();
    }
}

void TaskManager::AddTask(std::function<void()> task)
{
    const uint32_t start = m_startingQueue++;
    for (uint32_t i = 0; i < m_executors.size() + K * k_concurrency; ++i)
    {
        if (m_queues[(start + i) % k_concurrency].tryPush(task))
            return;
    }
    m_queues[start % k_concurrency].push(task);
}

bool TaskManager::areAllDone() const
{
    return std::all_of(m_queues.begin(), m_queues.end(),
                       [](auto& queue) { return queue.isEmpty(); });
}

TaskManager::~TaskManager()
{
    m_run = false;

    for (uint32_t i = 0; i < k_concurrency; ++i)
    {
        m_queues.at(i).shutdown();
        m_executors.at(i).join();
    }
}
