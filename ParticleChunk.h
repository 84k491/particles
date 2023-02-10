#pragma once

#include "IParticleGenerator.h"
#include "Particle.h"

#include <atomic>
#include <functional>
#include <SFML/Graphics.hpp>
#include <list>
#include <mutex>

class ParticleFactory;

class ParticleChunk
{
public:
    static constexpr size_t s_size = 64;

    ParticleChunk();

    auto & particles() { return m_particles; }
    const auto & coordinates() const { return m_coordinates; }
    void for_each_alive_particle(const std::function<bool(Particle &)> & cb);
    void fill(ParticleFactory & factory, const sf::Vector2f & point);

    size_t alive_count() const { return m_alive_count; }
    size_t dead_count() const { return total_size() - m_alive_count; }
    size_t total_size() const { return s_size; }

private:
    void mark_as_dead(Particle & p);

private:
    std::atomic<size_t> m_alive_count = {};

    std::vector<Particle> m_particles;
    std::vector<sf::Vertex> m_coordinates;

    mutable std::mutex m_mutex;
};
