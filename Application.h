#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "LockFreeList.h"
#include "ParticleChunk.h"
#include "PhysicsCore.h"
#include "Renderer.h"

#include <SFML/Graphics.hpp>
#include <memory>

// TODO handle window resize

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
    void generate_chunk(const sf::Vector2f & point) override;

private:
    sf::RenderWindow m_window;
    ParticleFactory m_factory;
    LockFreeList<ParticleChunk> m_particles;
    std::vector<std::unique_ptr<PhysicsCore>> m_physics_cores;
    Renderer m_renderer;
    EventHandler m_event_handler;
};
