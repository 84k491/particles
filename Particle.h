#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle()
        // : m_shape(m_weight, 4) // TODO use 10 as a point count
    {
    }

    Particle(const Particle&) = default;
    Particle(Particle&&) = default;
    ~Particle() = default;

public: // TODO make private
    sf::Vector2f m_velosity = {};
    sf::Vector2f m_acceleration = {};
    // sf::Color m_color;
    float m_weight = 2.f; // radius // TODO rename?
    sf::Vertex m_shape;
};
