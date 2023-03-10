#pragma once

#include "IMouseListener.h"

#include <SFML/Graphics.hpp>
#include <atomic>
#include <optional>
#include <string_view>

class GravityPoint final : public IMouseListener
{
public:
    GravityPoint() {}
    std::optional<sf::Vector2f> point() const;

private:
    void on_mouse_event(bool is_pressed, float x, float y) override;

private:
    std::string_view s;
    std::atomic_bool m_is_active = {};
    std::atomic<float> m_x_pos = {};
    std::atomic<float> m_y_pos = {};
};
