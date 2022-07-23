#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "PhysicsCore.h"

#include <SFML/Graphics.hpp>

#include <memory>

// TODO handle window resize

class Application {
    static constexpr size_t particle_amount_at_start = 500'000;
    static constexpr size_t cores_amount = 1;

    static constexpr size_t window_width = 1280;
    static constexpr size_t window_height = 960;
public:
    Application();
    void window_loop();

private:
    FpsCounter m_fps_counter;
    sf::RenderWindow m_window;
    GravityPoint m_gravity_point;
    std::vector<std::unique_ptr<PhysicsCore>> m_physics_cores;
    EventHandler m_event_handler;
};
