#pragma once
#include "Board.h";
#include "Player.h"
#include "Spawner.h"


class Game
{
private:
	int width;
	int height;
	Board board;
	Player player;
	Spawner spawner;
	
	bool playersTurn;
	bool gameover;
	bool enemyTurn;

public:
	Game();
	Game(int w, int h);
	~Game();

	void Run();

	void PlayerMove();

	int GetWidth();
	int GetHeight();
	bool isGameover();
	bool isPlayersTurn();
	bool isEnemyTurn();

	void setWidth(int w);
	void setHeight(int h);	
	void setBoardParams(int v, int h);
	void setGameOver(bool go);
	void setPlayersTurn(bool pt);
	void setEnemyTurn(bool et);

	bool isSquareEmpty(int x, int y);


	void deployPlayer(int xTile, int yTile);
	void deployObjects();
	void MoveEnemy(int i);
	void MoveAllEnemies();

	void SpawnNewObjects();

	void Refresh();
	void GameOver();

	void Launch();

	void CheckForKill(int x, int y);
	void CheckForStomp(int x, int y);
};