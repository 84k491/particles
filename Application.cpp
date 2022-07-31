#include "Application.h"
#include "TimeCounter.h"
#include "AverageCounter.h"

Application::Application()
    : m_window(sf::VideoMode(window_width, window_height), "Particle Sandbox")
    , m_particles(chunk_size, m_factory)
    , m_event_handler(m_window, *this)
{
    m_physics_cores.emplace_back(std::make_unique<PhysicsCore>(
        m_particles,
        *this,
        sf::Vector2f(window_width, window_height)
    ));

    std::cout << "Particle size: " << sizeof(Particle) << std::endl;
    std::cout << "Vertex size: " << sizeof(sf::Vertex) << std::endl;
}

void Application::window_loop()
{
    TimeCounter tc;
    AverageCounter<double> draw_time_counter;
    while (m_window.isOpen()) {
        m_event_handler.handle_events();
        m_window.clear(sf::Color(0, 0, 0, 255));

        m_particles.for_each_chunk([&](const auto & chunk) {
            const auto & vec = chunk.coordinates();
            m_window.draw(vec.data(), chunk.alive_count(), sf::Points);
        });

        m_window.display();
        m_fps_counter.on_frame_draw();
    }
    m_fps_counter.print_avg_fps();
    std::cout << "Average draw time: " << draw_time_counter.average() << std::endl;
}

void Application::on_mouse_event(bool is_pressed, float x, float y)
{
    if (!is_pressed) {
        return;
    }

    m_particles.new_chunk(sf::Vector2f(x, y));
}

void Application::on_particle_died(const sf::Vector2f & point)
{
    m_particles.new_chunk(point);
}
