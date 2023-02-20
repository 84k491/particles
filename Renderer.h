#pragma once

#include "EventHandler.h"
#include "FpsCounter.h"
#include "ParticleChunk.h"
#include "IList.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>

class Renderer // TODO move to a separate file
{
public:
    Renderer(sf::RenderWindow & window, IList<ParticleChunk> & particles);

    ~Renderer()
    {
        m_thread.join();
    }

    void window_loop();

private:
    IList<ParticleChunk> & m_particles;
    sf::RenderWindow & m_window; // TODO const?
    FpsCounter m_fps_counter;
    std::thread m_thread; // TODO worker?
};

