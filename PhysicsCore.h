#pragma once

#include "Particle.h"
#include "ParticleFactory.h"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <optional>

class PhysicsCore {
public:
    static constexpr float max_velosity = 1400.f;
    static constexpr size_t particle_amount_at_start = 2000;
    PhysicsCore();

    void calculate();
    void on_mouse_event(bool is_pressed, float x, float y);

public: // TODO make private
    ParticleFactory m_factory;
    std::vector<Particle> m_particles;
    std::optional<sf::Vector2f> m_gravity_point;
    std::chrono::time_point<std::chrono::system_clock> m_previous_calculation;
};
