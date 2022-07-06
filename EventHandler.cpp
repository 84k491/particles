#include "EventHandler.h"
#include "PhysicsCore.h"

EventHandler::EventHandler(sf::RenderWindow& window, GravityPoint& mouse_listener)
    : m_window(window)
    , m_mouse_listener(mouse_listener)
{
}

void EventHandler::handle_events()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::MouseButtonPressed:
            m_is_mouse_pressed = true;
            m_mouse_listener.on_mouse_event(
                m_is_mouse_pressed,
                event.mouseButton.x,
                event.mouseButton.y);
            break;
        case sf::Event::MouseButtonReleased:
            m_is_mouse_pressed = false;
            m_mouse_listener.on_mouse_event(
                m_is_mouse_pressed,
                event.mouseButton.x,
                event.mouseButton.y);
            break;
        case sf::Event::MouseMoved:
            m_mouse_listener.on_mouse_event(
                m_is_mouse_pressed,
                event.mouseMove.x,
                event.mouseMove.y);
            break;
        default:
            break;
        }
    }
}
