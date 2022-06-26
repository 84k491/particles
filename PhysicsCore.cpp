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

constexpr float constant_resistance_factor = -2.f;

PhysicsCore::PhysicsCore()
{
    for (size_t i = 0; i < particle_amount_at_start; ++i) {
        m_particles.emplace_back(m_factory.create_particle());
    }
}

void PhysicsCore::calculate()
{
    const auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> time_diff = now - m_previous_calculation;
    float time_coef = time_diff.count();
    m_previous_calculation = now;

    for (auto& p : m_particles) {
        sf::Vector2f acceleration(
            p.m_velosity.x * constant_resistance_factor,
            p.m_velosity.y * constant_resistance_factor);

        if (m_gravity_point.has_value()) {
            auto grav_acc = *m_gravity_point - p.m_position;
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

        p.m_position += p.m_velosity * time_coef;
        p.m_velosity += acceleration;

        float velosity_mod = std::min(vec_mod(p.m_velosity), (max_velosity / p.m_weight));
        uint8_t color_shift = std::round(255. * (velosity_mod / (max_velosity / p.m_weight)));

        uint8_t red = color_shift;
        uint8_t green = 255 - color_shift;
        uint8_t blue = 20;
        p.m_color = sf::Color(red, green, blue, 220);
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
