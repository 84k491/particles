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

    bool is_alive(const std::chrono::time_point<std::chrono::system_clock> & now) const
    {
        return m_time_to_die > now;
    }
    auto & shape() { return *m_shape; }
    const auto & shape() const { return *m_shape; }

public: // TODO make private?
    sf::Vector2f m_velosity = {};
    std::chrono::time_point<std::chrono::system_clock> m_time_to_die;

private:
    sf::Vertex * m_shape = nullptr;
};
