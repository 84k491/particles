#pragma once

#include "AverageCounter.h"

#include <chrono>
#include <iostream>

class FpsCounter {
public:
    FpsCounter() {}
    void on_frame_draw()
    {
        const auto now = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = now - m_previous;
        m_previous = now;
        m_current_fps = 1. / diff.count();
        m_avg_counter.push_value(m_current_fps);
    }

    auto fps() const { return m_current_fps; }
    void print_fps() const { std::cout << "Fps: " << m_current_fps << std::endl; }
    void print_avg_fps() const { std::cout << "Average fps: " << m_avg_counter.average() << std::endl; }

private:
    AverageCounter<size_t> m_avg_counter;
    std::chrono::time_point<std::chrono::system_clock> m_previous;
    float m_current_fps = 0.f;
};
