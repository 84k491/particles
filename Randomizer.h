#pragma once

#include <random>
#include <iostream>

// TODO add lower bound
class Randomizer
{
public:
    Randomizer()
    {
    }

    Randomizer(float lower_bound, float upper_bound)
        : m_generator(m_random_device())
        , m_distribution(lower_bound, upper_bound)
    {
    }

    float random_value() const { return m_distribution(m_generator); }

private:
    std::random_device m_random_device;
    mutable std::mt19937 m_generator;
    mutable std::uniform_real_distribution<float> m_distribution;
};

class ProbabilityRandomizer
{
public:
    ProbabilityRandomizer(float probability)
        : m_probability(probability)
        , m_randomizer(0.f, 1.f)
    {
    }

    bool value() const
    {
        const auto val = m_randomizer.random_value();
        return val < m_probability;
    }

    const float m_probability = 0.f;

private:
    Randomizer m_randomizer;
};

class SignRandomizer
{
public:
    SignRandomizer()
        : m_randomizer(.5f)
    {
    }

    int random_sign() const { return m_randomizer.value() ? 1 : -1; }

private:
    ProbabilityRandomizer m_randomizer;
};
