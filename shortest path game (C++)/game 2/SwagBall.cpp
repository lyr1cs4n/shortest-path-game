#include "SwagBall.h"

void SwagBall::initcircle(RenderTarget *  window)
{
	circle.setRadius(static_cast<float>(rand() %10 + 10));
	circle.setPosition(rand() % window->getSize().x-circle.getGlobalBounds().width, rand() % window->getSize().y - -circle.getGlobalBounds().height);
}

SwagBall::SwagBall(RenderTarget* window, int type) :type (type)
{
	this->initcircle(window);
}

SwagBall::~SwagBall()
{

}

int SwagBall::gettype()
{
	return type;
}

CircleShape& SwagBall::getshape()
{
	return circle;
}

void SwagBall::render(RenderTarget* Target)
{
	Target->draw(circle);
}
