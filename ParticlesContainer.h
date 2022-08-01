#pragma once

#include "IParticleGenerator.h"
#include "Particle.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <mutex>

class ParticlesContainer;
class ParticleFactory;
class ParticlesChunk // TODO rename module
{
    friend class ParticlesContainer;
    friend class ParticleFactory;
public:
    ParticlesChunk(size_t size);

    auto & particles() { return m_particles; }
    // auto & coordinates() { return m_coordinates; }
    const auto & coordinates() const { return m_coordinates; }

    // TODO if the dead ones placed behind iterator, there is no need to keep additional vector and move particles after
    void mark_as_dead(Particle & p);
    size_t alive_count() const { return m_alive_count; }
    size_t total_size() const { return m_coordinates.size(); }

private:
    size_t m_alive_count = 0;

    std::vector<Particle> m_particles;
    std::vector<sf::Vertex> m_coordinates;

    mutable std::mutex m_mutex;
};

class ParticlesContainer
{
public:
    ParticlesContainer(size_t chunk_size)
        : m_chunk_size(chunk_size)
    {
    }

    ParticlesChunk & new_chunk();
    void for_each_chunk(std::function<void(ParticlesChunk &)> && callback);

private:
    const size_t m_chunk_size = 0;
    std::list<ParticlesChunk> m_chunks;
};
