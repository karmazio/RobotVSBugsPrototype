#include "NonPlayerObj.h"

NonPlayerObj::NonPlayerObj()
{
}


NonPlayerObj::NonPlayerObj(int t, int x, int y)
{
	type = t;
	posX = x;
	posY = y;
}

int NonPlayerObj::getPosX()
{
	return posX;
}

int NonPlayerObj::getPosY()
{
	return posY;
}

int NonPlayerObj::getType()
{
	return type;
}




void NonPlayerObj::setPosX(int x)
{
	posX = x;
}

void NonPlayerObj::setPosY(int y)
{
	posY = y;
}


