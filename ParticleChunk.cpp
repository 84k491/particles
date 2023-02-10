#include "ParticleChunk.h"

#include "ParticleFactory.h"

#include <iostream>

ParticleChunk::ParticleChunk()
{
    std::lock_guard l(m_mutex);
    m_coordinates.resize(s_size);
}

void ParticleChunk::for_each_alive_particle(const std::function<bool(Particle &)> & cb)
{
    std::lock_guard l(m_mutex);

    for (size_t i = 0; i < m_alive_count; ++i) {
        auto & it = m_particles[i];
        const bool do_remove = cb(it);
        if (do_remove) {
            mark_as_dead(it);
        }
    }
}

void ParticleChunk::mark_as_dead(Particle & p)
{
    if (0 == m_alive_count) {
        return;
    }
    p = std::move(m_particles[--m_alive_count]);
}

void ParticleChunk::fill(ParticleFactory & factory, const sf::Vector2f & point)
{
    std::lock_guard l(m_mutex);
    std::cout << "Filling chunk" << std::endl;
    m_particles.clear();
    m_particles.reserve(total_size());

    for (size_t i = 0; i < total_size(); ++i) {
        m_particles.emplace_back(factory.create_particle(point, m_coordinates[i]));
    }

    m_alive_count = total_size();
}
