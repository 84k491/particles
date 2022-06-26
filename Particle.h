#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle()
    // : m_color(sf::Color(0, 255, 0, 150))
    {
    }

    Particle(const Particle&) = default;
    Particle(Particle&&) = default;
    ~Particle() = default;

    sf::CircleShape construct_shape() const
    {
        sf::CircleShape shape(m_weight);
        shape.setPosition(m_position);
        shape.setFillColor(m_color);
        return shape;
    }

public: // TODO make private
    sf::Vector2f m_position; // use shape as a storage
    sf::Vector2f m_velosity = {};
    sf::Vector2f m_acceleration = {};
    sf::Color m_color;
    float m_weight = 2.f; // radius // TODO rename?
};
