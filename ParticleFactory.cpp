#include "ParticleFactory.h"

ParticleFactory::ParticleFactory(const sf::Vector2f&, const sf::Vector2f& pos_br_border)
    : m_width_randomizer(pos_br_border.x) // TODO use left border too!
    , m_height_randomizer(pos_br_border.y) // TODO use top border too!
    , m_weight_randomizer(1.5f)
    , m_velosity_randomizer(3.f)
{
}

Particle ParticleFactory::create_particle()
{
    Particle particle;
    particle.m_position.x = m_width_randomizer.random_value();
    particle.m_position.y = m_height_randomizer.random_value();
    particle.m_weight = m_weight_randomizer.random_value();
    // particle.m_velosity.x = m_velosity_randomizer.random_value();
    // particle.m_velosity.y = m_velosity_randomizer.random_value();
    return particle;
}
