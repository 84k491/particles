#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "PhysicsCore.h"

#include <SFML/Graphics.hpp>

// TODO handle window resize

class Application {
public:
    Application();

    void render_loop(); // TODO move to renderer module

private:
    void draw_particles();

private:
    FpsCounter m_fps_counter;
    sf::RenderWindow m_window;
    PhysicsCore m_physics_core;
    EventHandler m_event_handler;
};
