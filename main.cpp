#include "Application.h"

#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>

#include <iostream>

// TODO mulithreaded rendering
// TODO hud?
// TODO use config

int main()
{
    XInitThreads();
    Application app;
    app.window_loop();
    return 0;
}
