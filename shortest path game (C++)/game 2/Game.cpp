#include "Game.h"

void Game::initializeVariables()
{
    maze = new Maze(window);
}
void Game::initializeWindow()
{
    videoMode.height = 800;
    videoMode.width = 700;

    window = new RenderWindow (videoMode,"Game 2",Style::Close | Style::Titlebar);
    window->setFramerateLimit(60);
}
void Game::startAgain()
{
    delete maze;
    system("cls");
    maze = new Maze(window);
}
void Game::PollEvents()
{
    Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.key.code == Keyboard::Escape)
        {
            window->close();
        }
        else if (ev.type == Event::Closed)
        {
            window->close();
        }
        else if ((ev.key.code == sf::Keyboard::R))
        {
            startAgain();
        }
    }
}
void Game::update()
{
    this->PollEvents();
}
bool Game::running()
{
    return true;
}
void Game::render()
{
    window->clear();
    maze->render(window);
    window->display();
}

Game::Game()
{
    this->initializeWindow();
    this->initializeVariables();
}
Game::~Game()
{
    delete window;
}
