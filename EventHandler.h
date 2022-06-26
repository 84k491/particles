#pragma once

#include <SFML/Graphics.hpp>

class PhysicsCore;

class EventHandler {
public:
    EventHandler(sf::RenderWindow& window, PhysicsCore& mouse_listener);

    void handle_events();

private:
    sf::RenderWindow& m_window;
    PhysicsCore& m_mouse_listener;
    bool m_is_mouse_pressed = false;
};
