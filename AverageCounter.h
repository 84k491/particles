#pragma once

#include <array>

class AverageCounter
{
    static constexpr size_t buf_size = 100;
public:
    AverageCounter();

    void push_value(size_t v);
    double average() const;

private:
    std::array<size_t, buf_size> m_buffer;
    size_t m_iterator = 0;
};

