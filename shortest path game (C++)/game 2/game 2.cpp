#include <SFML/Graphics.hpp>
#include "Game.h"
#include <ctime>
using namespace sf;

int main()
{
    Game game;

    do{
        game.render();
        game.update();


    } while (game.running());
}
