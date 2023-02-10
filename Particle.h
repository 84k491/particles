#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

class Particle {
public:
    Particle(sf::Vertex & shape)
        : m_shape(&shape)
    {
    }

    Particle(const Particle&) = default;
    Particle & operator =(const Particle& other) = delete;
    Particle(Particle&&) = default;
    Particle & operator =(Particle&& other)
    {
        m_velosity = other.m_velosity;
        m_time_to_die = other.m_time_to_die;
        *m_shape = *other.m_shape;
        return *this;
    }

    ~Particle() = default;

    bool is_alive()
    {
        if (m_is_alive) {
            // TODO get now moment from argument and remove flag
            m_is_alive = m_time_to_die > std::chrono::system_clock::now();
        }
        return m_is_alive;
    }
    auto & shape() { return *m_shape; }
    const auto & shape() const { return *m_shape; }

    void set_will_spawn_new(bool value) { m_will_spawn_new = value; }
    bool will_spawn_new() const { return m_will_spawn_new; }

public: // TODO make private?
    sf::Vector2f m_velosity = {};
    std::chrono::time_point<std::chrono::system_clock> m_time_to_die;

private:
    sf::Vertex * m_shape = nullptr;
    bool m_will_spawn_new = false;
    bool m_is_alive = true;
};
