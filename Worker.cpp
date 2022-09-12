#include "Worker.h"

Worker::Worker(std::function<void()> && cb)
    : m_stopped(false)
    , m_thread([this, cb](){ while (!m_stopped.load()) { cb(); } })
{
}

Worker::~Worker()
{
    m_stopped.store(true);
    m_thread.join();
}
