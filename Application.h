#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "PhysicsCore.h"

#include <SFML/Graphics.hpp>

#include <memory>

// TODO handle window resize

//                 |*******calculate_velosity2******|
// |*calc_pos2||dr||***calculate_velosity1**||cp1***|

class Application {
    static constexpr size_t particle_amount_at_start = 1'000'000;
public:
    Application();
    ~Application();

    void window_loop();

private:
    FpsCounter m_fps_counter;
    sf::RenderWindow m_window;
    GravityPoint m_gravity_point;
    PhysicsCore m_physics_core;
    EventHandler m_event_handler;
};
