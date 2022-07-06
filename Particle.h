#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle(sf::Vertex & shape)
        : m_shape(shape)
    {
    }

    Particle(const Particle&) = default;
    Particle(Particle&&) = default;
    ~Particle() = default;

public: // TODO make private?
    sf::Vector2f m_velosity = {};
    sf::Vector2f m_acceleration = {};
    sf::Vector2f m_position_shift = {};
    float m_weight = 2.f; // radius // TODO rename?
    sf::Vertex & m_shape;
    uint8_t m_color_shift = 0;
};
