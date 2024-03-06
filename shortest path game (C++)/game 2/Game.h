#pragma once

#include <iostream>
#include <sfml/Audio.hpp>
#include <sfml/graphics.hpp>
#include <sfml/system.hpp>
#include <sfml/network.hpp>
#include <sstream>
#include <chrono>
#include "Maze.h"
#include <thread>
#include <windows.h>

using namespace sf;


class Game
{
private:
    RenderWindow* window;
    Event ev;
    VideoMode videoMode;
    Maze* maze;



public:
    Game();
    virtual ~Game();

    void initializeWindow();
    void startAgain();
    void initializeVariables();

    bool running();
    void render();
    void PollEvents();
    void update();
};

