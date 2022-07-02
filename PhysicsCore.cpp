#include "PhysicsCore.h"

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

PhysicsCore::PhysicsCore(const sf::Vector2f& window_br_border)
    : m_br_border(sf::Vector2f(window_br_border.x - window_margin_px, window_br_border.y - window_margin_px))
    , m_tl_border(window_margin_px, window_margin_px)
    , m_factory(m_tl_border, m_br_border)
    , m_window_br_border(window_br_border)
    , m_particles(particle_amount_at_start, m_factory)
{
}

void PhysicsCore::calculate()
{
    const auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> time_diff = now - m_previous_calculation;
    float time_coef = time_diff.count();
    m_previous_calculation = now;

    for (auto & p : m_particles.particles()) {
        sf::Vector2f acceleration(
            p.m_velosity.x * constant_resistance_factor,
            p.m_velosity.y * constant_resistance_factor);

        if (m_gravity_point.has_value()) {
            auto grav_acc = *m_gravity_point - p.m_shape.position;
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
        p.m_shape.position += (p.m_velosity * time_coef);
        p.m_velosity += acceleration;

        float velosity_mod = std::min(vec_mod(p.m_velosity), (max_color_velosity / p.m_weight));
        uint8_t color_shift = std::round(255. * (velosity_mod / (max_color_velosity / p.m_weight)));

        uint8_t red = color_shift;
        uint8_t green = 255 - color_shift;
        uint8_t blue = 20;
        p.m_shape.color = sf::Color(red, green, blue, 120);
    }
}

void PhysicsCore::on_mouse_event(bool is_pressed, float x, float y)
{
    if (!is_pressed && m_gravity_point.has_value()) {
        m_gravity_point = {};
        return;
    }
    if (!is_pressed) {
        return;
    }

    m_gravity_point = std::make_optional<sf::Vector2f>(x, y);
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
