#pragma once

#include "Particle.h"
#include "Randomizer.h"
#include "IParticleGenerator.h"

class ParticleFactory final : public IParticleGenerator{
public:
    ParticleFactory(const sf::Vector2f& pos_tl_border, const sf::Vector2f& pos_br_border);
    Particle create_particle(sf::Vertex & vertex) const override;

private:
    Randomizer m_width_randomizer;
    Randomizer m_height_randomizer;
    Randomizer m_weight_randomizer;
    Randomizer m_velosity_randomizer;
};
