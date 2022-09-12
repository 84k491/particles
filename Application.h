#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "PhysicsCore.h"

#include <SFML/Graphics.hpp>

#include <memory>

// TODO handle window resize

class Renderer // TODO move to a separate file
{
public:
    Renderer(sf::RenderWindow & window, ParticlesContainer & particles);

    ~Renderer()
    {
        m_thread.join();
    }

    void window_loop();

private:
    ParticlesContainer & m_particles; // TODO make const!!!
    sf::RenderWindow & m_window; // TODO const?
    FpsCounter m_fps_counter;
    std::thread m_thread; //TODO worker?
};

class Application final
    : public IMouseListener
    , public IChunkGenerator
{
    static constexpr size_t chunk_size = 64;

    static constexpr size_t window_width = 1280;
    static constexpr size_t window_height = 960;
public:
    Application();
    void window_loop();

private:
    void on_mouse_event(bool is_pressed, float x, float y) override;
    void on_particle_died(const ParticlesChunk & chunk, const sf::Vector2f & point) override;

private:
    sf::RenderWindow m_window;
    ParticleFactory m_factory;
    ParticlesContainer m_particles;
    std::vector<std::unique_ptr<PhysicsCore>> m_physics_cores;
    Renderer m_renderer;
    EventHandler m_event_handler;
    ProbabilityRandomizer m_spawn_randomizer;
};
