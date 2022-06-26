#include "TimeCounter.h"

double TimeCounter::execution_time_in_sec(std::function<void()> && fn) const
{
    const auto start = std::chrono::system_clock::now();
    fn();
    const auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}
