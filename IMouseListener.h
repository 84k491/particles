#pragma once

class IMouseListener
{
public:
    virtual void on_mouse_event(bool is_pressed, float x, float y) = 0;
};
