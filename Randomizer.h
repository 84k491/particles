#pragma once

#include <random>

class Randomizer // TODO make mutable??
{
public:
    Randomizer(float upper_bound)
        : m_generator(m_random_device())
        , m_distribution(1.f, upper_bound)
    {
    }

    float random_value() { return m_distribution(m_generator); }

private:
    std::random_device m_random_device;
    std::mt19937 m_generator;
    std::uniform_real_distribution<float> m_distribution;
};

constexpr size_t window_width = 1280;
constexpr size_t window_height = 960;
