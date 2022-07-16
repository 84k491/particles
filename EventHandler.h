#pragma once

#include "IMouseListener.h"

#include <SFML/Graphics.hpp>

class EventHandler {
public:
    EventHandler(sf::RenderWindow& window, IMouseListener& mouse_listener);

    void handle_events();

private:
    sf::RenderWindow& m_window;
    IMouseListener& m_mouse_listener;
    bool m_is_mouse_pressed = false;
};
