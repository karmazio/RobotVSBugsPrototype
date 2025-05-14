#include "Player.h"

Player::Player()
{
	facing = 0;
	posX = 0;
	posY = 0;

	speed = 4;
	range = 4;
	shots = 1;
}

Player::Player(int x, int y)
{
	facing = 0;
	posX = x;
	posY = y;

	speed = 4;
	range = 4;
	shots = 1;
}

void Player::turnRight()
{
	facing--;

	if (facing < 0) {
		facing = 3;
	}
}

void Player::turnLeft()
{
	facing++;
	if (facing > 3) {
		facing = 0;
	}
}

void Player::setFacing(int f)
{
	facing = f;
}

void Player::setPosX(int x)
{
	posX = x;
}

void Player::setPosY(int y)
{
	posY = y;
}

void Player::setSpeed(int s)
{
	speed = s;
}

void Player::setRange(int r)
{
	range = r;
}

void Player::setShots(int s)
{
	shots = s;
}


int Player::getFacing()
{
	return facing;
}

int Player::getPosX()
{
	return posX;
}

int Player::getPosY()
{
	return posY;
}

int Player::getRange()
{
	return range;
}

int Player::getSpeed()
{
	return speed;
}

int Player::getShots()
{
	return shots;
}



void Player::Draw(int x, int y, int size)
{
	if (!sprite.LoadPNG("player 1 hand.png"))
	{
		throw std::exception("Failed to load image");
	}
	sprite.DrawTilted(x, y, size, size, facing * 90);
}
