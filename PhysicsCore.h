#pragma once

#include "AverageCounter.h"
#include "GravityPoint.h"
#include "ICalculationsProvider.h"
#include "LockFreeList.h"
#include "Particle.h"
#include "ParticleChunk.h"
#include "ParticleFactory.h"
#include "TimeCounter.h"
#include "Worker.h"

#include <SFML/Graphics.hpp>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

enum class BorderCrossing {
    None,
    Top,
    Bottom,
    Right,
    Left,
};

class IChunkGenerator // TODO move it to factory ? // TODO rename?
{
public:
    virtual void generate_chunk(const sf::Vector2f & point) = 0;
};

class PhysicsCore final
{
public:
    static constexpr float max_color_velosity = 1400.f;
    static constexpr unsigned window_margin_px = 5;
    static constexpr float gravity_coef = 9.f;

    PhysicsCore(
            LockFreeList<ParticleChunk> & particles,
            IChunkGenerator & chunk_generator,
            const sf::Vector2f& window_br_border);

private:
    void calculate();

    BorderCrossing if_out_of_borders(const Particle& p) const;
    void handle_border_crossing(Particle& p) const;

private:
    std::atomic_bool m_thread_stopped = false; // TODO try different memory order

    sf::Vector2f m_br_border;
    sf::Vector2f m_tl_border;
    sf::Vector2f m_window_br_border;
    std::chrono::time_point<std::chrono::system_clock> m_previous_calculation; // TODO add _time

    LockFreeList<ParticleChunk> & m_particles;
    IChunkGenerator & m_chunk_generator;

    AverageCounter<double> m_vel_calc_counter;
    AverageCounter<double> m_pos_calc_counter;

    Worker m_worker;
};
