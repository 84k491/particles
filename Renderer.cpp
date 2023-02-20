#include "Renderer.h"

#include "TimeCounter.h"

Renderer::Renderer(sf::RenderWindow & window, IList<ParticleChunk> & particles)
    : m_particles(particles)
    , m_window(window)
    , m_thread([&]() { window_loop(); })
{
}

void Renderer::window_loop()
{
    m_window.setActive(true);

    TimeCounter tc;
    AverageCounter<double> draw_time_counter;
    while (m_window.isOpen()) {
        m_window.clear(sf::Color(0, 0, 0, 255));

        m_particles.foreach([&](const ParticleChunk & chunk) -> bool {
            const auto & vec = chunk.coordinates();
            m_window.draw(vec.data(), chunk.alive_count(), sf::Points);
            return false;
        });

        m_window.display();
        m_fps_counter.on_frame_draw();
    }
    m_fps_counter.print_avg_fps();
    std::cout << "Average draw time: " << draw_time_counter.average() << std::endl;
}

