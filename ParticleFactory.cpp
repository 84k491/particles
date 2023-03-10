#include "ParticleFactory.h"
#include "ParticleChunk.h"

#include <iostream>
#include <mutex>

ParticleFactory::ParticleFactory()
    : m_velosity_randomizer(1.f, 500.f)
    , m_livetime_randomizer(10.f, 5000.f)
    , m_color_randomizer(20.f, 255.f)
    , m_spawn_randomizer(0.015f)
{
}

Particle ParticleFactory::create_particle(const sf::Vector2f & point, sf::Vertex & vertex) const
{
    Particle particle(vertex);
    vertex.position = point;
    particle.m_velosity = sf::Vector2f(
        m_sign_randomizer.random_sign() * m_velosity_randomizer.random_value(),
        m_sign_randomizer.random_sign() * m_velosity_randomizer.random_value());

    constexpr uint8_t red = 255;
    const uint8_t green = std::lround(m_color_randomizer.random_value());
    const uint8_t blue = std::lround(m_color_randomizer.random_value());
    constexpr uint8_t alpha = 255;
    vertex.color = sf::Color(red, green, blue, alpha);

    particle.m_time_to_die = std::chrono::system_clock::now() +
        std::chrono::milliseconds(std::lround(m_livetime_randomizer.random_value()));

    particle.set_will_spawn_new(m_spawn_randomizer.value());

    return particle;
}
