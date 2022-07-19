#include "Application.h"
#include "TimeCounter.h"
#include "AverageCounter.h"

Application::Application()
    : m_window(sf::VideoMode(window_width, window_height), "Particle Sandbox")
    , m_event_handler(m_window, m_gravity_point)
{
    for (size_t i = 0; i < cores_amount; ++i) {
        m_physics_cores.emplace_back(
            std::make_unique<PhysicsCore>(
                particle_amount_at_start / cores_amount,
                sf::Vector2f(window_width, window_height),
                m_gravity_point));
    }

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

        for (const auto & core : m_physics_cores) {
            core->wait_for_calculation_and_do([&](const auto & vec) {
                const auto draw_time = tc.execution_time_in_sec([&](){
                    m_window.draw(vec.data(), vec.size(), sf::Points);
                });
                draw_time_counter.push_value(draw_time);
            });
            core->request();
        }
        m_window.display();
        m_fps_counter.on_frame_draw();
    }
    m_fps_counter.print_avg_fps();
    std::cout << "Average draw time: " << draw_time_counter.average() << std::endl;
}
