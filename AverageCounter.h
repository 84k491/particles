#pragma once

#include <array>
#include <functional>
#include <numeric>

template<class T>
class AverageCounter {
    static constexpr size_t buf_size = 100;

public:
    AverageCounter()
    {
        m_buffer.fill(0);
    }

    void push_value(const T & v)
    {
        m_buffer[m_iterator] = v;
        m_iterator = (m_iterator + 1) % buf_size;
    }

    double average() const
    {
        T sum = {};
        for (const auto & v : m_buffer) {
            sum += v;
        }
        return static_cast<double>(sum) / buf_size;
    }

private:
    std::array<T, buf_size> m_buffer;
    size_t m_iterator = 0;
};
