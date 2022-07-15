#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "PhysicsCore.h"

#include <SFML/Graphics.hpp>

#include <memory>

// TODO handle window resize

class Application {
    static constexpr size_t particle_amount_at_start = 1'000'000;
    static constexpr size_t cores_amount = 2;
public:
    Application();
    ~Application();

    void window_loop();

private:
    FpsCounter m_fps_counter;
    sf::RenderWindow m_window;
    GravityPoint m_gravity_point;
    std::vector<std::unique_ptr<PhysicsCore>> m_physics_cores; // TODO make their lifetime match to app's
    EventHandler m_event_handler;
};
