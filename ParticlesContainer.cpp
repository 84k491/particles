#include "ParticlesContainer.h"
#include <iostream>

ParticlesChunk::ParticlesChunk(size_t size)
{
    m_coordinates.resize(size);
}

ParticlesChunk & ParticlesContainer::new_chunk()
{
    auto result_chunk = m_chunks.end();
    for (auto it = m_chunks.begin(), end = m_chunks.end(); it != end; ++it) {
        if (0 == it->alive_count()) {
            result_chunk = it;
            break;
        }
    }
    if (result_chunk == m_chunks.end()) {
        result_chunk = m_chunks.emplace(m_chunks.end(), m_chunk_size);
        std::cout << "Chunks size = " << m_chunks.size() << std::endl;
    }

    return *result_chunk;
}

void ParticlesContainer::for_each_chunk(std::function<void(ParticlesChunk &)> && callback)
{
    for (auto & chunk : m_chunks) {
        std::lock_guard cl{chunk.m_mutex};
        if (0 == chunk.alive_count()) {
            continue;
        }
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
}
