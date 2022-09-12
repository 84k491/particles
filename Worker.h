#pragma once

#include <atomic>
#include <functional>
#include <thread>

class Worker
{
public:
    Worker(std::function<void()> && cb);
    ~Worker();

private:
    std::atomic<bool> m_stopped = false;
    std::thread m_thread;
};
