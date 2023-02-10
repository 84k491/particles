#pragma once

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <utility>

template <class T>
class IList
{
public:
    virtual void emplace_front(std::function<void(T &)> && callback) = 0;
    virtual void foreach(std::function<bool(T &)> && callback) = 0; // true for remove
};

template <class T>
class LockFreeList : public IList<T>
{
    friend class Node;
    class Node
    {
        using SuperT = LockFreeList<T>;
        friend class LockFreeList<T>;

    public:
        Node(SuperT & parent)
            : m_data(std::make_shared<T>())
            , m_parent(parent)
        {
            m_parent.m_size.fetch_add(1);
            std::cout << "New node created. new size: " << m_parent.m_size.load() << std::endl;
        }

        ~Node()
        {
            m_parent.m_size.fetch_sub(1);
        }

        std::shared_ptr<Node> get_next_and_maybe_remove()
        {
            auto result = std::atomic_load(&m_next);
            while (result && result->must_be_removed()) {
                auto new_next = std::atomic_load(&result->m_next);
                while (!std::atomic_compare_exchange_weak(
                        &m_next,
                        &result,
                        new_next)) {
                }
            }
            return result;
        }

        auto data() const { return m_data; }
        void mark_to_remove() { m_remove_mark.store(true); }
        bool must_be_removed() const { return m_remove_mark.load(); }

    private:
        std::shared_ptr<Node> m_next = nullptr;
        std::atomic_bool m_remove_mark = false;

        std::shared_ptr<T> m_data;
        SuperT & m_parent;
    };

public:
    LockFreeList()
        : m_sentinel(std::make_shared<Node>(*this))
    {
    }

    void emplace_front(std::function<void(T &)> && callback) override
    {
        auto new_node = std::make_shared<Node>(*this);
        callback(*new_node->data());

        std::shared_ptr<Node> old_head = nullptr;
        do {
            old_head = m_sentinel->get_next_and_maybe_remove();
            new_node->m_next = old_head;
        } while(!std::atomic_compare_exchange_weak(&m_sentinel->m_next, &old_head, new_node));
    }

    void foreach(std::function<bool(T &)> && callback) override
    {
        for (auto node_sptr = m_sentinel->get_next_and_maybe_remove();
             node_sptr != nullptr;
             node_sptr = node_sptr->get_next_and_maybe_remove()) {

            if (callback(*node_sptr->data())) {
                node_sptr->mark_to_remove();
            }
        }
    }

    int size() { return m_size.load(); }

private:
    std::shared_ptr<Node> m_sentinel = nullptr;

    std::atomic<int> m_size = 0;
};
