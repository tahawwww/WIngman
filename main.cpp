#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1920,1080),"Wingman By Taha Manan",Style::Default);


    Game game(&window);
    // Game Loop
    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {window.close();}
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {window.close();}
        }

        game.Update();
        game.Draw();

    }
    return 0;
}
