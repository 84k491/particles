#include "ParticleFactory.h"
#include <iostream>

ParticleFactory::ParticleFactory()
    // : m_width_randomizer(pos_br_border.x) // TODO use left border too!
    // , m_height_randomizer(pos_br_border.y) // TODO use top border too!
    // : m_weight_randomizer(1.5f)
    : m_velosity_randomizer(300.f)
{
}

Particle ParticleFactory::create_particle(const sf::Vector2f & point, sf::Vertex & vertex) const
{
    Particle particle(vertex);
    vertex.position = point;
    // particle.m_weight = m_weight_randomizer.random_value();
    particle.m_velosity = sf::Vector2f(
        m_sign_randomizer.random_sign() * m_velosity_randomizer.random_value(),
        m_sign_randomizer.random_sign() * m_velosity_randomizer.random_value());

    constexpr uint8_t red = 255;
    constexpr uint8_t green = 0;
    constexpr uint8_t blue = 125;
    constexpr uint8_t alpha = 255;
    vertex.color = sf::Color(red, green, blue, alpha);

    particle.m_time_to_die = std::chrono::system_clock::now() + std::chrono::seconds(1); // TODO randomize

    return particle;
}
