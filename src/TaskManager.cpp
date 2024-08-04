#include "TaskManager.h"
#include <algorithm>
#include <chrono>
#include <queue>
#include <thread>

namespace
{
constexpr uint32_t K = 20;
const uint32_t k_concurrency = std::thread::hardware_concurrency();
} // namespace

TaskManager::TaskManager()
{
    m_startingQueue = 0;

    m_queues.reserve(k_concurrency);
    for (uint32_t i = 0; i < k_concurrency; ++i)
    {
        m_queues.emplace_back(std::make_unique<TaskQueue>());
        m_executors.emplace_back([this, i]() { run(i); });
    }
}

void TaskManager::run(uint32_t thread_id)
{
    while (m_run)
    {
        std::function<void()> task;
        for (uint32_t i = 0; i < m_executors.size() + K * k_concurrency; ++i)
        {
            if (m_queues[(thread_id + i) % k_concurrency]->tryPop(task))
                break;
        }
        if (!task && !m_queues[thread_id]->pop(task))
            break;
        task();
    }
}

void TaskManager::AddTask(std::function<void()> task)
{
    const uint32_t start = m_startingQueue++;
    for (uint32_t i = 0; i < m_executors.size() + K * k_concurrency; ++i)
    {
        if (m_queues[(start + i) % k_concurrency]->tryPush(task))

            return;
    }
    m_queues[start % k_concurrency]->push(task);
}

bool TaskManager::areAllDone() const
{
    return std::all_of(m_queues.begin(), m_queues.end(),
                       [](auto& queue) { return queue->isEmpty(); });
}

TaskManager::~TaskManager()
{
    m_run = false;
    for (uint32_t i = 0; i < k_concurrency; ++i)
    {
        m_queues[i]->shutdown();
        m_executors[i].join();
    }
}
