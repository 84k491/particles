#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "PhysicsCore.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <thread>

// TODO handle window resize

class Application {
public:
    Application();

    void window_loop();

private:
    FpsCounter m_fps_counter;
    sf::RenderWindow m_window;
    PhysicsCore m_physics_core;
    EventHandler m_event_handler;
};
