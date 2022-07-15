#include "ParticleFactory.h"
#include <iostream>

ParticleFactory::ParticleFactory(const sf::Vector2f&, const sf::Vector2f& pos_br_border)
    : m_width_randomizer(pos_br_border.x) // TODO use left border too!
    , m_height_randomizer(pos_br_border.y) // TODO use top border too!
    , m_weight_randomizer(1.5f)
    , m_velosity_randomizer(3.f)
{
}

Particle ParticleFactory::create_particle(sf::Vertex & vertex)
{
    Particle particle(vertex);
    vertex.position = sf::Vector2f(m_width_randomizer.random_value(), m_height_randomizer.random_value());
    particle.m_weight = m_weight_randomizer.random_value();

    const uint8_t red = 255 * (particle.m_weight / (1.5f - 1.f)); // TODO use randomizer lower bound
    const uint8_t green = 255 - red;
    constexpr uint8_t blue = 25;
    constexpr uint8_t alpha = 120;
    vertex.color = sf::Color(red, green, blue, alpha);

    return particle;
}
