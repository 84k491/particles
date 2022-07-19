#include "PhysicsCore.h"
#include "GravityPoint.h"

// TODO move those functions to the header
float vec_mod(const sf::Vector2f& pt)
{
    return std::sqrt(pt.x * pt.x + pt.y * pt.y);
}

void normalize(sf::Vector2f& pt)
{
    const auto mod = vec_mod(pt);
    pt.x /= mod;
    pt.y /= mod;
}

constexpr float constant_resistance_factor = -2.f; // TODO move to header

PhysicsCore::PhysicsCore(size_t particles_amount, const sf::Vector2f& window_br_border, GravityPoint & gravity_point)
    : m_br_border(sf::Vector2f(window_br_border.x - window_margin_px, window_br_border.y - window_margin_px))
    , m_tl_border(window_margin_px, window_margin_px)
    , m_factory(m_tl_border, m_br_border)
    , m_window_br_border(window_br_border)
    , m_particles(particles_amount, m_factory)
    , m_gravity_point(gravity_point)
    , m_worker([this]{ calculate(); })
{
}

PhysicsCore::~PhysicsCore()
{
    request();
    m_thread_stopped = true;
    m_worker.join();
}

void PhysicsCore::calculate()
{
    TimeCounter tc;
    while (!m_thread_stopped) {
        m_vel_calc_counter.push_value(tc.execution_time_in_sec([this]() { calculate_velosity(); }));

        wait_for_request_and_do([&](){
            m_pos_calc_counter.push_value(tc.execution_time_in_sec([this]() { calculate_position(); }));
        });
    }
    std::cout << "Average velocity calculation time: " << m_vel_calc_counter.average() << std::endl;
    std::cout << "Average position calculation time: " << m_pos_calc_counter.average() << std::endl;
}

void PhysicsCore::calculate_velosity()
{
    const auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> time_diff = now - m_previous_calculation;
    float time_coef = time_diff.count();
    m_previous_calculation = now;

    const auto gravity_point = m_gravity_point.point();

    for (auto & p : m_particles.particles()) {
        sf::Vector2f acceleration(
            p.m_velosity.x * constant_resistance_factor,
            p.m_velosity.y * constant_resistance_factor);

        if (gravity_point.has_value()) {
            auto grav_acc = *gravity_point - p.m_shape.position;
            const auto mod = vec_mod(grav_acc);
            normalize(grav_acc);
            float effective_radius = 1000.f;
            float coefficient = effective_radius - mod;
            coefficient /= 13.f;
            coefficient *= coefficient;
            if (coefficient < 0.f) {
                coefficient = 0.f;
            }
            grav_acc *= coefficient;
            acceleration += grav_acc;
        }
        acceleration /= p.m_weight;
        acceleration *= time_coef;

        handle_border_crossing(p);
        p.m_velosity += acceleration;
        p.m_position_shift = p.m_velosity * time_coef;
    }
}

void PhysicsCore::calculate_position()
{
    for (auto & p : m_particles.particles()) {
        p.m_shape.position += (p.m_position_shift);
    }
}

BorderCrossing PhysicsCore::if_out_of_borders(const Particle& p) const
{
    const auto& pos = p.m_shape.position;
    if (pos.x > m_br_border.x) {
        return BorderCrossing::Right;
    }
    if (pos.y > m_br_border.y) {
        return BorderCrossing::Bottom;
    }
    if (pos.x < m_tl_border.x) {
        return BorderCrossing::Left;
    }
    if (pos.y < m_tl_border.y) {
        return BorderCrossing::Top;
    }
    return BorderCrossing::None;
}

void PhysicsCore::handle_border_crossing(Particle& p) const
{
    const auto crossed = if_out_of_borders(p);

    switch (crossed) {
    case BorderCrossing::Top:
    case BorderCrossing::Bottom:
        p.m_velosity.y = -p.m_velosity.y;
        break;
    case BorderCrossing::Left:
    case BorderCrossing::Right:
        p.m_velosity.x = -p.m_velosity.x;
        break;
    case BorderCrossing::None:
    default:
        return;
    };
}
