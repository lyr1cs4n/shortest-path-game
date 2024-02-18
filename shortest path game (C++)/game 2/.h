#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>

using namespace sf;

class SwagBall
{
private:
	CircleShape circle;
	int type;

	void initcircle(RenderTarget* window);

public:
	SwagBall(RenderTarget* window , int type);
	virtual ~SwagBall();

	int gettype();
	CircleShape& getshape();
	void render(RenderTarget* Target);

};


