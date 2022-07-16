#pragma once

#include "IParticleGenerator.h"
#include "Particle.h"

#include <SFML/Graphics.hpp>

class ParticlesContainer
{
public:
    ParticlesContainer(size_t size, IParticleGenerator & generator);

    void push_back(Particle && p);

    auto & particles() { return m_particles; }
    const auto & coordinates() { return m_coordinates; }

private:
    std::vector<Particle> m_particles;
    std::vector<sf::Vertex> m_coordinates;
};
