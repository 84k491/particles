#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class GravityPoint
{
public:
    GravityPoint() {}
    void on_mouse_event(bool is_pressed, float x, float y);
    std::optional<sf::Vector2f> m_gravity_point;
};
