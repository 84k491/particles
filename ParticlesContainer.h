#pragma once

#include "Particle.h"

#include <SFML/Graphics.hpp>

class ParticleFactory;
class ParticlesContainer
{
public:
    ParticlesContainer(size_t size, ParticleFactory & generator); // TODO use interface

    void push_back(Particle && p);

    auto & particles() { return m_particles; }
    const auto & coordinates() { return m_coordinates; }

private:
    std::vector<Particle> m_particles;
    std::vector<sf::Vertex> m_coordinates;
};
