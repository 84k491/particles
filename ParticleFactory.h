#pragma once

#include "Particle.h"
#include "Randomizer.h"
#include "IParticleGenerator.h"

class SignRandomizer // TODO make something more accurate?
{
public:
    SignRandomizer()
        : m_randomizer(3.f)
    {
    }

    int random_sign() const { return m_randomizer.random_value() > 2.f ? 1 : -1; }

private:
    Randomizer m_randomizer;
};

class ParticleFactory final : public IParticleGenerator{
public:
    ParticleFactory();
    Particle create_particle(const sf::Vector2f & point, sf::Vertex & vertex) const override;

private:
    // Randomizer m_width_randomizer;
    // Randomizer m_height_randomizer;
    // Randomizer m_weight_randomizer;
    Randomizer m_velosity_randomizer;
    SignRandomizer m_sign_randomizer;
};
