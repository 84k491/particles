#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "LockFreeList.h"
#include "ParticleChunk.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>

class Renderer // TODO move to a separate file
{
public:
    Renderer(sf::RenderWindow & window, LockFreeList<ParticleChunk> & particles);

    ~Renderer()
    {
        m_thread.join();
    }

    void window_loop();

private:
    LockFreeList<ParticleChunk> & m_particles; // TODO make const!!!
    sf::RenderWindow & m_window; // TODO const?
    FpsCounter m_fps_counter;
    std::thread m_thread; //TODO worker?
};

