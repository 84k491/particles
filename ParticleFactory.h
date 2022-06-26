#pragma once

#include "Particle.h"
#include "Randomizer.h"

class ParticleFactory {
public:
    ParticleFactory(const sf::Vector2f& pos_tl_border, const sf::Vector2f& pos_br_border);
    Particle create_particle();

private:
    Randomizer m_width_randomizer;
    Randomizer m_height_randomizer;
    Randomizer m_weight_randomizer;
    Randomizer m_velosity_randomizer;
};
