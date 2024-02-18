#include "Player.h"

void Player::initplayer(float x, float y)
{
	player.setPosition(x, y);
}
Player::Player(float x, float y)
{
	this->initplayer(x,y);
	this->initTexture();

}
void Player::initTexture()
{
	if (!texture.loadFromFile("Materials/character_idle_0.png"))
	{
		std::cout<<"Could Not Load Player Texture\n";
	}
	player.setTexture(texture);

}
Sprite& Player::getplayer()
{
	return player;
}

Player::~Player()
{

}

