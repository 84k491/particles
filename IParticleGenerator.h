#pragma once

#include "Particle.h"

class IParticleGenerator
{
public:
    virtual Particle create_particle(const sf::Vector2f & point, sf::Vertex & vertex) const = 0;
};
