#pragma once

#include "IParticleGenerator.h"
#include "Particle.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <mutex>

class ParticlesContainer;
class ParticlesChunk // TODO rename module
{
    friend class ParticlesContainer;
public:
    ParticlesChunk(const sf::Vector2f & point, size_t size, IParticleGenerator & generator);

    auto & particles() { return m_particles; }
    const auto & coordinates() const { return m_coordinates; }

    // TODO if the dead ones placed behind iterator, there is no need to keep additional vector and move particles after
    void mark_as_dead(Particle & p);
    size_t alive_count() const { return m_alive_count; }

private:
    size_t m_alive_count = 0;

    std::vector<Particle> m_particles;
    std::vector<sf::Vertex> m_coordinates;

    mutable std::mutex m_mutex;
};

class ParticlesContainer
{
public:
    ParticlesContainer(size_t chunk_size, IParticleGenerator & particle_generator)
        : m_chunk_size(chunk_size)
        , m_particle_generator(particle_generator)
    {
    }

    void new_chunk(const sf::Vector2f & pt);
    void for_each_chunk(std::function<void(ParticlesChunk &)> && callback);

private:
    const size_t m_chunk_size = 0;
    IParticleGenerator & m_particle_generator;
    std::list<ParticlesChunk> m_chunks;
    std::mutex m_list_mutex;
};
