#pragma once
#include "glfwbgi.h"

class Player
{
private:
	Graph::Image sprite;
	int facing;
	int posX;
	int posY;

	int speed;
	int range;
	int shots;
public:
	Player();
	Player(int x, int y);
	void turnLeft();
	void turnRight();

	void setFacing(int f);
	void setPosX(int x);
	void setPosY(int y);
	void setSpeed(int s);
	void setRange(int r);
	void setShots(int s);


	int getFacing();
	int getPosX();
	int getPosY();
	int getRange();
	int getSpeed();
	int getShots();

	void Draw(int x, int y, int size);

};
