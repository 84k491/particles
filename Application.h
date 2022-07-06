#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "PhysicsCore.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <thread>

// TODO handle window resize

class Application {
    static constexpr size_t particle_amount_at_start = 1'000'000;
public:
    Application();

    void window_loop();

private:
    FpsCounter m_fps_counter;
    sf::RenderWindow m_window;
    GravityPoint m_gravity_point;
    PhysicsCore m_physics_core;
    EventHandler m_event_handler;
};
