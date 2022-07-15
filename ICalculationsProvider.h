#pragma once

#include <SFML/Graphics.hpp>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <vector>

class ICalculationsProvider
{
public:
    void request();
    void wait_for_calculation_and_do(std::function<void(const std::vector<sf::Vertex> &)> && cb);

protected:
    void wait_for_request_and_do(std::function<void()> && cb);
    virtual const std::vector<sf::Vertex> & get_data() = 0;

private:
    std::condition_variable m_provider_cv;
    std::condition_variable m_consumer_cv;
    bool m_need_calculation = false;
    std::mutex m_mutex;
};

