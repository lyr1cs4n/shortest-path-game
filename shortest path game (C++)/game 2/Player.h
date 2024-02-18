#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace sf;
using namespace std;

class Player
{
private:
	Sprite player;
	Texture texture;

	void initplayer(float x, float y);
	void initTexture();
	

public:
	Sprite& getplayer();
	Player(float x, float y);
	virtual ~Player();

	
};


