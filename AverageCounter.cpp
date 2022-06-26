#include "AverageCounter.h"

#include <numeric>
#include <iostream>
#include <functional>

AverageCounter::AverageCounter()
{
    m_buffer.fill(0);
}

void AverageCounter::push_value(size_t v)
{
    m_buffer[m_iterator] = v;
    m_iterator = (m_iterator + 1) % buf_size;
}

double AverageCounter::average() const
{
    const size_t sum = std::accumulate(m_buffer.begin(), m_buffer.end(), 0);
    return static_cast<double>(sum) / buf_size;
}
