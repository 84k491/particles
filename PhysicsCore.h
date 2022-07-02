#pragma once

#include "Particle.h"
#include "ParticleFactory.h"
#include "ParticlesContainer.h"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <optional>

enum class BorderCrossing {
    None,
    Top,
    Bottom,
    Right,
    Left,
};

class PhysicsCore {
public:
    static constexpr float max_color_velosity = 1400.f;
    static constexpr size_t particle_amount_at_start = 1'000'000;
    static constexpr size_t calc_threads_count = 1;
    static constexpr unsigned window_margin_px = 5;

    PhysicsCore(const sf::Vector2f& window_br_border);

    void calculate();
    void on_mouse_event(bool is_pressed, float x, float y);

private:
    BorderCrossing if_out_of_borders(const Particle& p) const;
    void handle_border_crossing(Particle& p) const;

public: // TODO make private
    sf::Vector2f m_br_border;
    sf::Vector2f m_tl_border;
    ParticleFactory m_factory;
    sf::Vector2f m_window_br_border;
    ParticlesContainer m_particles;
    std::optional<sf::Vector2f> m_gravity_point;
    std::chrono::time_point<std::chrono::system_clock> m_previous_calculation; // TODO add _time
};
