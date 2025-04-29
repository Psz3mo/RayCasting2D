#include "Engine.h"

int main()
{
    RenderWindow window;
    Engine engine(window,800, 600);
    engine.run();

    return 0;
}