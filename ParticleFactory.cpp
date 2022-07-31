#include "ParticleFactory.h"
#include <iostream>

ParticleFactory::ParticleFactory()
    // : m_width_randomizer(pos_br_border.x) // TODO use left border too!
    // , m_height_randomizer(pos_br_border.y) // TODO use top border too!
    // : m_weight_randomizer(1.5f)
    : m_velosity_randomizer(300.f)
    , m_livetime_randomizer(2000.f)
    , m_color_randomizer(255.f)
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

    const uint8_t red = std::lround(m_color_randomizer.random_value());
    const uint8_t green = std::lround(m_color_randomizer.random_value());
    constexpr uint8_t blue = 225;
    constexpr uint8_t alpha = 255;
    vertex.color = sf::Color(red, green, blue, alpha);

    particle.m_time_to_die = std::chrono::system_clock::now() +
        std::chrono::milliseconds(1000 + std::lround(m_livetime_randomizer.random_value()));

    return particle;
}
