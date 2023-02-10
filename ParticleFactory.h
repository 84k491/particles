#pragma once

#include "Particle.h"
#include "Randomizer.h"
#include "IParticleGenerator.h"

class ParticleChunk;
class ParticleFactory final : public IParticleGenerator{
public:
    ParticleFactory();
    Particle create_particle(const sf::Vector2f & point, sf::Vertex & vertex) const override;

private:
    Randomizer m_velosity_randomizer;
    Randomizer m_livetime_randomizer;
    Randomizer m_color_randomizer;
    SignRandomizer m_sign_randomizer;
    ProbabilityRandomizer m_spawn_randomizer;
};
