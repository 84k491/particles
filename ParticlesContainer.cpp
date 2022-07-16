#include "ParticlesContainer.h"
#include <iostream>

ParticlesContainer::ParticlesContainer(size_t size, IParticleGenerator & generator)
{
    m_coordinates.resize(size);
    m_particles.reserve(size);

    for (size_t i = 0; i < size; ++i) {
        m_particles.emplace_back(generator.create_particle(m_coordinates[i]));
    }
}
