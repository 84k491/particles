#include "Application.h"
#include "TimeCounter.h"
#include "AverageCounter.h"

Application::Application()
    : m_window(sf::VideoMode(window_width, window_height), "Particle Sandbox") // TODO store window sizes as local cosnt
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
    for (auto & t : m_textures) {
        if (!t.create(window_width, window_height))
        {
            std::cout << "Some error when creating texture" << std::endl;
        }
    }
}

Renderer::~Renderer()
{
    stop();
}

void Renderer::draw_particles()
{
    for (size_t i = 0; i < m_physics_core.m_particles.size() / 2; ++i) {
        m_textures[0].draw(m_physics_core.m_particles[i].m_shape);
    }
    for (size_t i = m_physics_core.m_particles.size() / 2; i < m_physics_core.m_particles.size(); ++i) {
        m_textures[1].draw(m_physics_core.m_particles[i].m_shape);
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
    AverageCounter<double> texture_draw_avg_counter;
    AverageCounter<double> window_draw_avg_counter;
    AverageCounter<double> calc_avg_counter;
    AverageCounter<double> clean_avg_counter;

    while (m_window.isOpen()) {
        const auto clean_time = tc.execution_time_in_sec([this](){
            m_window.clear(sf::Color(0, 0, 0, 255));
            m_textures[0].clear(sf::Color(0, 0, 0, 0));
            m_textures[1].clear(sf::Color(0, 0, 0, 0));
        });

        const auto draw_time_at_texture = tc.execution_time_in_sec([this](){ draw_particles(); });

        sf::Sprite sprite0(m_textures[0].getTexture());
        sf::Sprite sprite1(m_textures[1].getTexture());
        const auto draw_time_at_window = tc.execution_time_in_sec([&](){
            m_window.draw(sprite0);
            m_window.draw(sprite1);
        });
        m_window.display();

        m_fps_counter.on_frame_draw();
        const auto calculation_time = tc.execution_time_in_sec([this](){ m_physics_core.calculate(); }); // TODO move to another thread

        texture_draw_avg_counter.push_value(draw_time_at_texture);
        calc_avg_counter.push_value(calculation_time);
        window_draw_avg_counter.push_value(draw_time_at_window);
        clean_avg_counter.push_value(clean_time);
    }
    std::cout << "clean avg time: " << clean_avg_counter.average() << "s" << std::endl;
    std::cout << "draw texture avg time: " << texture_draw_avg_counter.average() << "s" << std::endl;
    std::cout << "draw window avg time: " << window_draw_avg_counter.average() << "s" << std::endl;
    std::cout << "calculation avg time: " << calc_avg_counter.average() << "s" << std::endl;
}
