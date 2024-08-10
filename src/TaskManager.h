#pragma once

#include "TaskQueue.h"

#include <atomic>
#include <cstdint>
#include <functional>
#include <thread>
#include <vector>

class TaskManager
{
  public:
    TaskManager();
    ~TaskManager();

    void AddTask(std::function<void()> task);

    bool areAllDone() const;

  private:
    void run(uint32_t thread_id);

    bool m_run{true};
    const uint32_t k_concurrency = 8; // std::thread::hardware_concurrency();
    std::atomic<uint32_t> m_startingQueue;
    std::vector<TaskQueue> m_queues{k_concurrency};
    std::vector<std::thread> m_executors;
};
