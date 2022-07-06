#pragma once

#include <SFML/Graphics.hpp>

class GravityPoint;

class EventHandler {
public:
    EventHandler(sf::RenderWindow& window, GravityPoint& mouse_listener);

    void handle_events();

private:
    sf::RenderWindow& m_window;
    GravityPoint& m_mouse_listener;
    bool m_is_mouse_pressed = false;
};
