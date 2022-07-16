#include "GravityPoint.h"

void GravityPoint::on_mouse_event(bool is_pressed, float x, float y)
{
    m_is_active.store(is_pressed);
    m_x_pos.store(x);
    m_y_pos.store(y);
}

std::optional<sf::Vector2f> GravityPoint::point() const
{
    if (!m_is_active.load()) {
        return std::nullopt;
    }

    return std::make_optional(sf::Vector2f(m_x_pos.load(), m_y_pos.load()));
}
