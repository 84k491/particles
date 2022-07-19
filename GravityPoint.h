#pragma once

#include "IMouseListener.h"

#include <SFML/Graphics.hpp>
#include <optional>
#include <atomic>

class GravityPoint final : public IMouseListener
{
public:
    GravityPoint() {}
    std::optional<sf::Vector2f> point() const;

private:
    void on_mouse_event(bool is_pressed, float x, float y) override;

private:
    std::atomic_bool m_is_active = false;
    std::atomic<float> m_x_pos = 0.f;
    std::atomic<float> m_y_pos = 0.f;
};
