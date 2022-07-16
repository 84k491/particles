#pragma once

#include "Particle.h"

class IParticleGenerator
{
public:
    virtual Particle create_particle(sf::Vertex & vertex) const = 0;
};
