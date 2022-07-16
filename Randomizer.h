#pragma once

#include <random>

// TODO add lower bound
class Randomizer
{
public:
    Randomizer(float upper_bound)
        : m_generator(m_random_device())
        , m_distribution(1.f, upper_bound)
    {
    }

    float random_value() const { return m_distribution(m_generator); }

private:
    std::random_device m_random_device;
    mutable std::mt19937 m_generator;
    mutable std::uniform_real_distribution<float> m_distribution;
};
