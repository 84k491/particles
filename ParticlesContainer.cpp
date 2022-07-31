#include "ParticlesContainer.h"
#include <iostream>

ParticlesChunk::ParticlesChunk(const sf::Vector2f & point, size_t size, IParticleGenerator & generator)
{
    m_coordinates.resize(size);
    m_particles.reserve(size);

    for (size_t i = 0; i < size; ++i) {
        m_particles.emplace_back(generator.create_particle(point, m_coordinates[i]));
    }

    m_alive_count = size;
}

void ParticlesContainer::new_chunk(const sf::Vector2f & pt)
{
    std::lock_guard l{m_list_mutex};
    m_chunks.emplace(m_chunks.end(), pt, m_chunk_size, m_particle_generator);
}

void ParticlesContainer::for_each_chunk(std::function<void(ParticlesChunk &)> && callback)
{
    std::lock_guard l{m_list_mutex};
    for (auto & chunk : m_chunks) {
        std::lock_guard cl{chunk.m_mutex};
        callback(chunk);
        // TODO do mark_as_dead here
    }
}

void ParticlesChunk::mark_as_dead(Particle & p)
{
    if (0 == m_alive_count) {
        return;
    }
    p = m_particles[m_alive_count-- - 1];
    std::cout << "m_alive_count = " << m_alive_count << std::endl;
}
