#include "Application.h"
#include "TimeCounter.h"
#include "AverageCounter.h"

Application::Application()
    : m_window(sf::VideoMode(window_width, window_height), "Particle Sandbox") // TODO store window sizes as local cosnt
    // , m_physics_core(particle_amount_at_start, sf::Vector2f(window_width, window_height), m_gravity_point)
    , m_event_handler(m_window, m_gravity_point) // TODO unsafe access to physics core
{
    for (size_t i = 0; i < cores_amount; ++i) {
        m_physics_cores.emplace_back(
            std::make_unique<PhysicsCore>(
                particle_amount_at_start / cores_amount,
                sf::Vector2f(window_width, window_height),
                m_gravity_point));
    }
}

Application::~Application()
{
    // TODO do i need it at all??
    for (auto & ptr : m_physics_cores) {
        ptr.reset();
    }
}

void Application::window_loop()
{
    // TimeCounter tc;
    // AverageCounter<double> window_draw_avg_counter;
    // AverageCounter<double> calc_avg_counter;
    // AverageCounter<double> clean_avg_counter;

    while (m_window.isOpen()) {
        m_event_handler.handle_events();

        // const auto clean_time = tc.execution_time_in_sec([this]() {
        // });
        m_window.clear(sf::Color(0, 0, 0, 255));

        // std::cout << "waiting for physics core calculations" << std::endl;
        for (const auto & ptr : m_physics_cores) {
            std::unique_lock ul(ptr->m_calc_mutex);
            ptr->m_draw_cond_var.wait(ul, [&]{ return !ptr->m_need_calculation; });

            // std::cout << "drawing vertexes" << std::endl;
            m_window.draw(ptr->m_particles.coordinates().data(), ptr->m_particles.coordinates().size(), sf::Points);
            ul.unlock();

            // std::cout << "requesting calculations" << std::endl;
            {
                std::lock_guard l(ptr->m_calc_mutex);
                ptr->m_need_calculation = true;
            }
            ptr->m_calc_cond_var.notify_all();
        }

        // std::cout << "displaying window" << std::endl;
        m_window.display();

        m_fps_counter.on_frame_draw();
        // const auto calculation_time = tc.execution_time_in_sec([this](){ m_physics_core.calculate(); });

        // calc_avg_counter.push_value(calculation_time);
        // window_draw_avg_counter.push_value(draw_time_at_window);
        // clean_avg_counter.push_value(clean_time);
    }
    // std::cout << "clean avg time: " << clean_avg_counter.average() << "s" << std::endl;
    // std::cout << "draw window avg time: " << window_draw_avg_counter.average() << "s" << std::endl;
    // std::cout << "calculation avg time: " << calc_avg_counter.average() << "s" << std::endl;
    m_fps_counter.print_avg_fps();
    // std::cout << "velosity calculation average time: "<< m_physics_core.m_vel_calc_counter.average() << std::endl;
    // std::cout << "position calculation average time: " << m_physics_core.m_pos_calc_counter.average() << std::endl;

}
