#include <chrono>
#include <functional>

class TimeCounter
{
public:
    TimeCounter() {}

    double execution_time_in_sec(std::function<void()> && fn) const;
};
