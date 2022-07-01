#include "Application.h"

#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>

#include <iostream>

// TODO mulithreaded rendering
// TODO check resized textures
// TODO try to calculate only half of particles but draw all of them

// TODO hud?
// TODO use config

// TODO remove debug build

int main()
{
    XInitThreads();
    Application app;
    app.window_loop();
    return 0;
}
