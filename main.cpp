#include <SFML/Graphics.hpp>

#include "Application.h"

#include <iostream>

// TODO handle window borders
// TODO mulithreaded rendering
// TODO mulithreaded calculations

int main()
{
    Application app;
    app.render_loop();
    return 0;
}
