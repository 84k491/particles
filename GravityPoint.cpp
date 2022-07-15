#include "GravityPoint.h"

void GravityPoint::on_mouse_event(bool is_pressed, float x, float y)
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
