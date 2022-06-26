#include "Application.h"
#include "TimeCounter.h"
#include "AverageCounter.h"

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
    for (const auto & p : m_physics_core.m_particles) {
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

    TimeCounter tc;
    AverageCounter<double> draw_avg_counter;
    AverageCounter<double> calc_avg_counter;

    while (m_window.isOpen()) {
        m_window.clear();

        const auto draw_time = tc.execution_time_in_sec([this](){ draw_particles(); });
        m_window.display();

        m_fps_counter.on_frame_draw();
        const auto calculation_time = tc.execution_time_in_sec([this](){ m_physics_core.calculate(); }); // TODO move to another thread

        draw_avg_counter.push_value(draw_time);
        calc_avg_counter.push_value(calculation_time);
    }
    std::cout << "draw avg time: " << draw_avg_counter.average() << "s" << std::endl;
    std::cout << "calculation avg time: " << calc_avg_counter.average() << "s" << std::endl;
}
