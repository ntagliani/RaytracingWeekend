#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>

class TaskQueue
{
  public:
    TaskQueue() = default;
    TaskQueue(const TaskQueue&) = delete;
    TaskQueue(TaskQueue&&) = delete;
    TaskQueue& operator=(const TaskQueue&) = delete;
    TaskQueue& operator=(TaskQueue&&) = delete;
    ~TaskQueue() = default;

    bool tryPop(std::function<void()>& job)
    {
        std::unique_lock<std::mutex> l(m_mutex, std::try_to_lock);
        if (m_stop || !l.owns_lock() || m_queue.empty())
            return false;
        job = m_queue.front();
        m_queue.pop_front();
        return true;
    }

    bool tryPush(std::function<void()> job)
    {
        {
            std::unique_lock<std::mutex> l(m_mutex, std::try_to_lock);
            if (m_stop || !l.owns_lock())
                return false;
            m_queue.push_back(job);
        }
        m_cv.notify_one();
        return true;
    }

    void push(std::function<void()> job)
    {
        {
            std::unique_lock<std::mutex> l(m_mutex);
            m_queue.push_back(job);
        }
        m_cv.notify_one();
    }

    bool pop(std::function<void()>& job)
    {
        std::unique_lock<std::mutex> l(m_mutex);
        while (m_queue.empty() && !m_stop)
            m_cv.wait(l);

        if (m_queue.empty() || m_stop)
            return false;
        job = m_queue.front();
        m_queue.pop_front();
        return true;
    }

    void shutdown()
    {
        {
            std::unique_lock<std::mutex> l(m_mutex);
            m_stop = true;
        }
        m_cv.notify_all();
    }

    bool isEmpty() const
    {
        std::unique_lock<std::mutex> l(m_mutex);
        return m_queue.empty();
    }

  private:
    bool m_stop{false};
    std::deque<std::function<void()>> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;
};
