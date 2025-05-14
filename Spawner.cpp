#include "Spawner.h"
#include "NonPlayerObj.h"
#include <iostream>
#include <cmath>

Spawner::Spawner()
{
	turn = 1;
	killScore = 0;


}

int Spawner::getTurn()
{
	return turn;
}

std::vector<NonPlayerObj>& Spawner::list()
{
	return npos;
}

int Spawner::getScore()
{
	return killScore;
}

void Spawner::setTurn(int t)
{
	turn = t;
}

void Spawner::setScore(int score)
{
	killScore = score;
}

void Spawner::setNpos(std::vector<NonPlayerObj> newNpos)
{
	npos = newNpos;
}

bool Spawner::randChance(int chance)
{
	srand((int)time(0));
	int r = rand() % 100;

	return r < 100;
}

void Spawner::Spawn(int type, int x, int y)
{
		NonPlayerObj toAdd(type, x, y);
		npos.push_back(toAdd);
}

void Spawner::Kill(int index)
{
	npos.erase(npos.begin() + index);
}


//int Spawner::findEmptyX(int playerPosX, int playerPosY)
//{
//	return 0;
//}
//
//
//int Spawner::findEmptyY(int playerPosX, int playerPosY)
//{
//	return 0;
//}
//

//void Spawner::MoveAll()
//{
//	for (int i = 0; i < list().size(); i++) {
//
//
//	}
//}
