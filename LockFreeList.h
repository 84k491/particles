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
    using super = LockFreeList<T>;
    public:
        Node(super & parent, Node* next_node)
            : m_next(next_node)
            , m_parent(parent)
        {
            m_parent.m_size.fetch_add(1);
        }

        ~Node()
        {
            std::cout << "NODE DESTRUCTOR" << std::endl;
            m_parent.m_size.fetch_sub(1);
        }

        auto get_next_and_maybe_remove()
        {
            auto result = m_next.load();
            while (result && result->must_be_removed()) {
                result = result->m_next.load();
                auto * old_node = m_next.exchange(result);
                delete old_node;
                std::cout << "removed. new size: " << m_parent.size() << std::endl;
            }
            return result;
        }

    auto data() const { return m_data; }
    void mark_to_remove() { m_remove_mark.store(true); }
    bool must_be_removed() const { return m_remove_mark.load(); }

    private:
        std::atomic<Node*> m_next;
        std::atomic_bool m_remove_mark;

        std::shared_ptr<T> m_data = nullptr;
        super & m_parent;
    };

public:
    LockFreeList()
    {
    }

    void emplace_front(std::function<void(T &)> && callback) override
    {
        std::cout << "emplacing.. " << std::endl;
        auto new_node = new Node(*this, m_head);
        callback(*new_node->data());

        auto old_head = m_head.load();
        while(!m_head.compare_exchange_weak(old_head, new_node)){}
    }

    void foreach(std::function<bool(T &)> && callback) override
    {
        for (auto * node_sptr = m_head.load();
             node_sptr != nullptr;
             node_sptr = node_sptr->get_next_and_maybe_remove()) {

            if (callback(*node_sptr->data())) {
                node_sptr->mark_to_remove();
            }
        }
    }

    int size() { return m_size.load(); }

private:
    std::atomic<Node*> m_head = nullptr;

    std::atomic<int> m_size = 0;
};
