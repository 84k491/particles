#pragma once

template <class T>
class IList {
public:
    virtual void emplace_front(std::function<void(T &)> && callback) = 0;
    virtual void foreach(std::function<bool(T &)> && callback) = 0;
};
