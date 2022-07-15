#pragma once

#include "Particle.h"
#include "ParticleFactory.h"
#include "ParticlesContainer.h"
#include "AverageCounter.h"
#include "TimeCounter.h"
#include "ICalculationsProvider.h"
#include "GravityPoint.h"

#include <SFML/Graphics.hpp>
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

class PhysicsCore final : public ICalculationsProvider
{
public:
    static constexpr float max_color_velosity = 1400.f;
    static constexpr unsigned window_margin_px = 5;

    PhysicsCore(size_t particles_amount, const sf::Vector2f& window_br_border, GravityPoint & gravity_point);
    ~PhysicsCore();

private:
    void calculate();
    void calculate_velosity();
    void calculate_position();

    BorderCrossing if_out_of_borders(const Particle& p) const;
    void handle_border_crossing(Particle& p) const;

    const std::vector<sf::Vertex> & get_data() override { return m_particles.coordinates(); }

private: // TODO make private
    bool m_thread_stopped = false; // TODO make atomic

    sf::Vector2f m_br_border;
    sf::Vector2f m_tl_border;
    ParticleFactory m_factory;
    sf::Vector2f m_window_br_border;
    ParticlesContainer m_particles;
    std::optional<sf::Vector2f> & m_gravity_point;
    std::chrono::time_point<std::chrono::system_clock> m_previous_calculation; // TODO add _time

    AverageCounter<double> m_vel_calc_counter;
    AverageCounter<double> m_pos_calc_counter;

    std::thread m_worker;
};
