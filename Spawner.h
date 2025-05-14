#pragma once
#include "glfwbgi.h"
#include <vector>
#include "NonPlayerObj.h"
using namespace Graph;
class Spawner {
private:
	int turn;
	std::vector<NonPlayerObj> npos;
	int killScore;

public:

	Spawner();

	int getTurn();
	std::vector<NonPlayerObj>& list();
	int getScore();

	void setTurn(int t);
	void setScore(int score);
	void setNpos(std::vector<NonPlayerObj> newNpos);

	bool randChance(int chance);

	//int findEmptyX(int playerPosX, int playerPosY);
	//int findEmptyY(int playerPosX, int playerPosY);


	void Spawn(int type, int x, int y);
	void Kill(int index);
	//void MoveAll();

};