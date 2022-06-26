#include "ParticleFactory.h"

ParticleFactory::ParticleFactory()
    : m_width_randomizer(window_width)
    , m_height_randomizer(window_height)
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
    // std::cout << "created a particle. x: " << particle.m_position.x << ", y: " << particle.m_position.y << std::endl;
    return particle;
}
