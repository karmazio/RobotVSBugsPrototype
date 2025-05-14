#include "glfwbgi.h"
#include <iostream>
#include <vector>
#include "Game.h"

using namespace Graph;





int main()
{
	Game g;
	g.setHeight(1080);
	g.setWidth(1200);
	g.setBoardParams(8, 8);
	//printf("W: %d, H: %d", g.GetWidth(), g.GetHeight());
	g.Launch();


	return 0;
}


