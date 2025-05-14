#pragma once
#include "glfwbgi.h"

class NonPlayerObj {

private:
	
	int type;
	int posX;
	int posY;

public:
	NonPlayerObj();
	NonPlayerObj(int t, int x, int y);

	int getPosX();
	int getPosY();
	int getType();



	void setPosX(int x);
	void setPosY(int y);

};