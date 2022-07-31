#include "ParticleFactory.h"
#include <iostream>

ParticleFactory::ParticleFactory()
    // : m_width_randomizer(pos_br_border.x) // TODO use left border too!
    // , m_height_randomizer(pos_br_border.y) // TODO use top border too!
    // : m_weight_randomizer(1.5f)
    // , m_velosity_randomizer(3.f)
{
}

Particle ParticleFactory::create_particle(const sf::Vector2f & point, sf::Vertex & vertex) const
{
    Particle particle(vertex);
    vertex.position = point;
    // particle.m_weight = m_weight_randomizer.random_value();

    constexpr uint8_t red = 255;
    constexpr uint8_t green = 0;
    constexpr uint8_t blue = 25;
    constexpr uint8_t alpha = 120;
    vertex.color = sf::Color(red, green, blue, alpha);

    particle.m_time_to_die = std::chrono::system_clock::now() + std::chrono::seconds(1); // TODO randomize

    return particle;
}
