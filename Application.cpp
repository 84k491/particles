#include "Application.h"

Application::Application()
    : m_window(sf::VideoMode(window_width, window_height), "Particle Sandbox")
    , m_physics_core(sf::Vector2f(window_width, window_height))
    , m_event_handler(m_window, m_physics_core) // TODO unsafe access to physics core
    , m_renderer(m_physics_core, m_window)
{
    m_window.setActive(false);
}

void Application::window_loop()
{
    m_renderer.start();
    while (m_window.isOpen()) {
        m_event_handler.handle_events();
    }
    m_renderer.stop();
}

Renderer::Renderer(PhysicsCore& physics_core, sf::RenderWindow& window)
    : m_physics_core(physics_core)
    , m_window(window)
{
}

Renderer::~Renderer()
{
    stop();
}

void Renderer::draw_particles()
{
    for (const auto p : m_physics_core.m_particles) {
        m_window.draw(p.m_shape);
    }
}

void Renderer::start()
{
    m_worker = std::make_unique<std::thread>([this]() { this->work(); });
}

void Renderer::stop()
{
    if (!m_worker) {
        return;
    }

    m_worker->join();
    m_worker.reset();
    m_fps_counter.print_avg_fps();
}

void Renderer::work()
{
    m_window.setActive(true);

    while (m_window.isOpen()) {
        m_window.clear();

        const auto start = std::chrono::system_clock::now();

        draw_particles();
        const auto particles_drawed = std::chrono::system_clock::now();

        m_window.display();
        const auto buffer_dispayed = std::chrono::system_clock::now();

        m_fps_counter.on_frame_draw();
        m_physics_core.calculate(); // TODO move to another thread

        const auto calculations_done = std::chrono::system_clock::now();

        std::chrono::duration<double> particles_drawed_time = particles_drawed - start;
        std::chrono::duration<double> calc_done_time = calculations_done - buffer_dispayed;

        std::cout << "particles_drawed_time: " << particles_drawed_time.count() << "s" << std::endl;
        std::cout << "calc_done_time: " << calc_done_time.count() << "s" << std::endl;
    }
}
