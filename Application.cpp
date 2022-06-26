#include "Application.h"

Application::Application()
    : m_window(sf::VideoMode(window_width, window_height), "SFML works!")
    , m_event_handler(m_window, m_physics_core)
{
}

void Application::render_loop()
{
    while (m_window.isOpen())
    {
        m_event_handler.handle_events();

        m_window.clear();
        draw_particles();
        m_window.display();

        m_fps_counter.on_frame_draw();
        // m_fps_counter.print_fps();

        m_physics_core.calculate();
    }
}

void Application::draw_particles()
{
    for (const auto p : m_physics_core.m_particles) {
        const auto shape = p.construct_shape();
        m_window.draw(shape);
    }
}
