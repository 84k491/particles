#include "Application.h"
#include "AverageCounter.h"

Application::Application()
    : m_window(sf::VideoMode(window_width, window_height), "Particle Sandbox")
    , m_particles()
    , m_renderer(m_window, m_particles)
    , m_event_handler(m_window, *this)
{
    m_window.setFramerateLimit(60);
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
    while (m_window.isOpen()) {
        m_event_handler.handle_events();
    }
}

void Application::on_mouse_event(bool is_pressed, float x, float y)
{
    if (!is_pressed) {
        return;
    }

    generate_chunk(sf::Vector2f(x, y));
}

void Application::generate_chunk(const sf::Vector2f & point)
{
    m_particles.emplace_front([&](auto & chunk) {
        chunk.fill(m_factory, point);
    });
}
