#pragma once

#include "Particle.h"
#include "ParticleFactory.h"
#include "ParticlesContainer.h"
#include "AverageCounter.h"
#include "TimeCounter.h"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <iostream>

enum class BorderCrossing {
    None,
    Top,
    Bottom,
    Right,
    Left,
};

class GravityPoint
{
public:
    GravityPoint() {}
    void on_mouse_event(bool is_pressed, float x, float y);
    std::optional<sf::Vector2f> m_gravity_point; // TODO rename this or class
};

class PhysicsCore {
public:
    static constexpr float max_color_velosity = 1400.f;
    static constexpr unsigned window_margin_px = 5;

    PhysicsCore(size_t particles_amount, const sf::Vector2f& window_br_border, GravityPoint & gravity_point);

    void calculate()
    {
        // std::cout << "        physics core worker loop init" << std::endl;
        TimeCounter tc;
        while (!m_thread_stopped) {
            // std::cout << "        calculating velosity" << std::endl;
            m_vel_calc_counter.push_value(tc.execution_time_in_sec([this]() { calculate_velosity(); }));

            // std::cout << "        waiting for pos calculations to be needed" << std::endl;
            std::unique_lock<std::mutex> ul{m_calc_mutex};
            m_calc_cond_var.wait(ul, [this]{ return m_need_calculation; });

            // std::cout << "        calculating positions" << std::endl;
            m_pos_calc_counter.push_value(tc.execution_time_in_sec([this]() { calculate_position(); }));
            // std::cout << "        about to notify that positions calculated" << std::endl;
            m_need_calculation = false;
            m_draw_cond_var.notify_all();

            // std::cout << "        end of loop" << std::endl;
        }
    }
    void calculate_velosity();
    void calculate_position();

private:
    BorderCrossing if_out_of_borders(const Particle& p) const;
    void handle_border_crossing(Particle& p) const;


public:
    std::condition_variable m_calc_cond_var;
    std::condition_variable m_draw_cond_var;
    bool m_need_calculation = false;
    std::mutex m_calc_mutex;
    bool m_thread_stopped = false;

    sf::Vector2f m_br_border;
    sf::Vector2f m_tl_border;
    ParticleFactory m_factory;
    sf::Vector2f m_window_br_border;
    ParticlesContainer m_particles;
    std::optional<sf::Vector2f> & m_gravity_point;
    std::chrono::time_point<std::chrono::system_clock> m_previous_calculation; // TODO add _time

    AverageCounter<double> m_vel_calc_counter;
    AverageCounter<double> m_pos_calc_counter;
};
