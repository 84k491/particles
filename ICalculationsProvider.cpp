#include "ICalculationsProvider.h"


void ICalculationsProvider::request()
{
    std::lock_guard l(m_mutex);
    m_need_calculation = true;
    m_provider_cv.notify_all();
}

void ICalculationsProvider::wait_for_calculation_and_do(std::function<void(const std::vector<sf::Vertex> &)> && cb)
{
    std::unique_lock ul(m_mutex);
    m_consumer_cv.wait(ul, [&]{ return !m_need_calculation; });
    cb(get_data());
}

void ICalculationsProvider::wait_for_request_and_do(std::function<void()> && cb)
{
    std::unique_lock<std::mutex> ul{m_mutex};
    m_provider_cv.wait(ul, [this]{ return m_need_calculation; });
    cb();
    m_need_calculation = false;
    m_consumer_cv.notify_all();
}
