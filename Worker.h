#include <atomic>
#include <functional>
#include <thread>

class Worker
{
public:
    Worker(std::function<void()> && cb)
        , m_thread([&, cb](){ while (!m_stopped.load()) { cb(); } })
    {
    }

    ~Worker()
    {
        m_stopped.store(true);
        m_thread.join();
    }


private:
    std::atomic<bool> m_stopped = false;
    std::thread m_thread;
};
