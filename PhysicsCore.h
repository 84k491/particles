#pragma once

#include "Particle.h"
#include "ParticleFactory.h"
#include "ParticlesContainer.h"
#include "AverageCounter.h"
#include "TimeCounter.h"
#include "ICalculationsProvider.h"
#include "GravityPoint.h"

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

class IChunkGenerator // TODO move it to factory
{
public:
    virtual void on_particle_died(const sf::Vector2f & point) = 0;
};

class PhysicsCore final// : public ICalculationsProvider
{
public:
    static constexpr float max_color_velosity = 1400.f;
    static constexpr unsigned window_margin_px = 5;
    static constexpr float gravity_coef = 9.f;
    static constexpr float constant_resistance_factor = -2.f;

    PhysicsCore(
        ParticlesContainer & particles,
        IChunkGenerator & chunk_generator,
        const sf::Vector2f& window_br_border);
    ~PhysicsCore();

private:
    void calculate();

    BorderCrossing if_out_of_borders(const Particle& p) const;
    void handle_border_crossing(Particle& p) const;

    // const std::vector<sf::Vertex> & get_data() override { return m_particles.coordinates(); }

private:
    std::atomic_bool m_thread_stopped = false; // TODO try different memory order

    sf::Vector2f m_br_border;
    sf::Vector2f m_tl_border;
    sf::Vector2f m_window_br_border;
    std::chrono::time_point<std::chrono::system_clock> m_previous_calculation; // TODO add _time

    ParticlesContainer & m_particles;
    IChunkGenerator & m_chunk_generator;

    AverageCounter<double> m_vel_calc_counter;
    AverageCounter<double> m_pos_calc_counter;

    std::thread m_worker;
};
