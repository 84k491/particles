#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "PhysicsCore.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <thread>

// TODO handle window resize

class Renderer {
public:
    Renderer(PhysicsCore& physics_core, sf::RenderWindow& window);
    ~Renderer();

    void start();
    void stop();

private:
    void work();

    void draw_particles();

private:
    PhysicsCore& m_physics_core;
    sf::RenderWindow& m_window;
    FpsCounter m_fps_counter;
    std::unique_ptr<std::thread> m_worker;
    std::array<sf::RenderTexture, 2> m_textures; // place it like levels, one on top of the other
};

class Application {
public:
    Application();

    void window_loop();

private:
    sf::RenderWindow m_window;
    PhysicsCore m_physics_core;
    EventHandler m_event_handler;
    Renderer m_renderer;
};
