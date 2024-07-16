#pragma once

#include "TaskQueue.h"

#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
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
    std::atomic<uint32_t> m_startingQueue;
    std::vector<std::unique_ptr<TaskQueue>> m_queues;
    std::vector<std::thread> m_executors;
};
