#include "Game.h"
#include "glfwbgi.h"
#include "Player.h"

#include "NonPlayerObj.h"
#include "Spawner.h"
#include <iostream>


using namespace Graph;


Game::Game()
{

	player.setPosX(0);
	player.setPosY(0);
	height = 720;
	width = 1980;
	gameover = false;
	enemyTurn = false;
}

Game::Game(int w, int h)
{
	player.setPosX(0);
	player.setPosY(0);
	width = w;
	height = h;
	gameover = false;
	enemyTurn = false;
}

Game::~Game()
{
	CloseGraph();
}



int Game::GetWidth()
{
	return width;
}

int Game::GetHeight()
{
	return height;
}

bool Game::isGameover()
{
	return gameover;
}

bool Game::isPlayersTurn()
{
	return playersTurn;
}

bool Game::isEnemyTurn()
{
	return enemyTurn;
}

void Game::setWidth(int w)
{
	width = w;
}

void Game::setHeight(int h)
{
	height = h;
}

void Game::setBoardParams(int h, int v)
{
	board.setHorSq(h);
	board.setVerSq(v);

	int hCut = width / h;
	int vCut = height * 0.8 / v;

	board.setTileSize(hCut < vCut ? hCut : vCut);
}

void Game::setGameOver(bool go)
{
	gameover = go;
}

void Game::setPlayersTurn(bool pt)
{
	playersTurn = pt;
}

void Game::setEnemyTurn(bool et)
{
	enemyTurn = et;
}

bool Game::isSquareEmpty(int x, int y)
{
	if (player.getPosX() == x && player.getPosY() == y) {
		printf("Square %d,%d is occupied\n", x, y);
		return false;
	}

	for (int i = 0; i < spawner.list().size(); i++) {
		if (spawner.list()[i].getPosX() == x &&
			spawner.list()[i].getPosY() == y) {
			printf("Square %d,%d is occupied\n", x, y);
			return false;
		}
	}
	printf("Square %d,%d is free to advance\n", x, y);
	return true;
}

void Game::deployPlayer(int xTile, int yTile)
{
	int x = (xTile + 0.5) * board.getTileSize();
	int y = (yTile + 0.5) * board.getTileSize();
	player.Draw(x, y, board.getTileSize());
}

void Game::deployObjects()
{
	Image bugIcon;
	if (!bugIcon.LoadPNG("bug.png"))
	{
		throw std::exception("Failed to load image");
	}
	Image speedUpIcon;
	if (!speedUpIcon.LoadPNG("speed boost.png"))
	{
		throw std::exception("Failed to load image");
	}
	Image rangeUpIcon;
	if (!rangeUpIcon.LoadPNG("range boost.png"))
	{
		throw std::exception("Failed to load image");
	}
	Image secondLaserIcon;
	if (!secondLaserIcon.LoadPNG("x2 laser.png"))
	{
		throw std::exception("Failed to load image");
	}



	for (int i = 0; i < spawner.list().size(); i++) {
		int x = (spawner.list()[i].getPosX() + 0.5) * board.getTileSize();
		int y = (spawner.list()[i].getPosY() + 0.5) * board.getTileSize();
		printf("An object found at %d,%d\n", spawner.list()[i].getPosX(), spawner.list()[i].getPosY());
		

		switch (spawner.list()[i].getType()) {
		case 1:
			bugIcon.DrawTilted(x,y, board.getTileSize() * 0.7, board.getTileSize() * 0.7, 0);
			break;
		case 2:
			speedUpIcon.DrawTilted(x,y, board.getTileSize(), board.getTileSize(), 0);
			break;
		case 3:
			rangeUpIcon.DrawTilted(x,y, board.getTileSize(), board.getTileSize(), 0);
			break;
		case 4:
			secondLaserIcon.DrawTilted(x,y, board.getTileSize(), board.getTileSize(), 0);
			break;
		}
	}
}

void Game::MoveEnemy(int i)
{
	int movesLeft = 3;
	while (movesLeft > 0) {
		// going forward
		int x = spawner.list()[i].getPosX();
		int y = spawner.list()[i].getPosY();
		if (isSquareEmpty(x, y + 1)) 
		{
			spawner.list()[i].setPosY(y + 1);
		}
		// detour to the right
		else if (isSquareEmpty(x + 1, y + 1) &&
			x + 1 < board.getHorSq()) 
		{
			spawner.list()[i].setPosY(y + 1);
			spawner.list()[i].setPosX(x + 1);
		}
		// detour to the left
		else if (isSquareEmpty(x - 1, y + 1) &&
			x - 1 > 0)
		{
			spawner.list()[i].setPosY(y + 1);
			spawner.list()[i].setPosX(x - 1);
		}

	
		Delay(250);
		Refresh();
		movesLeft--;
		printf("Moving a bug, moves left: %d\n", movesLeft);

		// Check gameover
		if (spawner.list()[i].getPosY() == board.getVerSq()) {
			setGameOver(true);
			GameOver();
		}
	}
}

void Game::MoveAllEnemies()
{
	for (int i = 0; i < spawner.list().size(); i++) {
		if (spawner.list()[i].getType() == 1) {
			MoveEnemy(i);
		}
	}
	setEnemyTurn(false);
	//setPlayersTurn(true);
}

int RandRange(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void Game::SpawnNewObjects()
{
	int enemiesToSpawn = 0;
	int chanceToSpawn = 40 + spawner.getTurn() * 10;
	srand((int)time(0));

	while (chanceToSpawn > 100) {
		enemiesToSpawn++;
		chanceToSpawn -= 100;
	}
	if (spawner.randChance(chanceToSpawn)) {
		enemiesToSpawn++;
	}

	for (int i = 0; i < enemiesToSpawn; i++) {
		int x = player.getPosX();
		int y = player.getPosY();
		while (!isSquareEmpty(x, y)) {
			x = RandRange(0, board.getHorSq() - 1);
			y = RandRange(0, 1);
		}
		NonPlayerObj toAdd(1, x, y);
		printf("Enemy spawned!\n");
		spawner.list().push_back(toAdd);
		Refresh();
		Delay(350);
	}
	// spawn speed boost
	if (spawner.randChance(20 + spawner.getTurn() * 5)) {
		int x = player.getPosX();
		int y = player.getPosY();
		while (!isSquareEmpty(x, y)) {
			x = RandRange(0, board.getHorSq() - 1);
			y = RandRange(0, board.getVerSq() - 1);
		}
		NonPlayerObj toAdd(2, x, y);
		printf("Speed boost spawned!\n");
		spawner.list().push_back(toAdd);
		Refresh();
		Delay(350);
	}

	// spawn range boost
	if (spawner.randChance(20 + spawner.getTurn() * 5)) {
		int x = player.getPosX();
		int y = player.getPosY();
		while (!isSquareEmpty(x, y)) {
			x = RandRange(0, board.getHorSq() - 1);
			y = RandRange(0, board.getVerSq() - 1);
		}
		NonPlayerObj toAdd(3, x, y);
		printf("Range boost spawned!\n");
		spawner.list().push_back(toAdd);
		Refresh();
		Delay(350);
	}

	// spawn Second laser 
	if (spawner.randChance(10 + spawner.getTurn() * 2)) {
		int x = player.getPosX();
		int y = player.getPosY();
		while (!isSquareEmpty(x, y)) {
			x = RandRange(0, board.getHorSq() - 1);
			y = RandRange(0, board.getVerSq() - 1);
		}
		NonPlayerObj toAdd(3, x, y);
		printf("Second laser spawned!\n");
		spawner.list().push_back(toAdd);
		Refresh();
		Delay(350);
	}





	spawner.setTurn(spawner.getTurn() + 1);
	setPlayersTurn(true);
}

void Game::Refresh() {
	ClearDevice(Color::Black);
	board.Draw(width, height);
	deployPlayer(player.getPosX(), player.getPosY());
	//printf("Spawner has %d objects on the board\n", spawner.list().size());
	deployObjects();
	SwapBuffers();
}

void Game::GameOver()
{

	Image go;
	if (!go.LoadPNG("gameover.png"))
	{
		throw std::exception("Failed to load image");
	}

	go.DrawTilted(width / 2, height / 2, width, height, 0);
	SwapBuffers();
	Delay(2000);

	//CloseGraph();

	Run();


}

void Game::Launch()
{
	InitGraph(width, height, "Robot vs Bugs");
	Run();
}

void Game::CheckForKill(int x, int y)
{
	for (int i = 0; i < spawner.list().size(); i++) {
		if (x == spawner.list()[i].getPosX()
			&& y == spawner.list()[i].getPosY() &&
			spawner.list()[i].getType() == 1) {
			spawner.Kill(i);
			spawner.setScore(spawner.getScore() + 1);
		}
	}
}

void Game::CheckForStomp(int x, int y) {
	for (int i = 0; i < spawner.list().size(); i++) {
		if (x == spawner.list()[i].getPosX()
			&& y == spawner.list()[i].getPosY()) {
			int newStat = 0;
			switch (spawner.list()[i].getType())
			{
			case 1:
			{
				spawner.Kill(i);
				spawner.setScore(spawner.getScore() + 1);
			}
			break;
			case 2:
			{
				spawner.Kill(i);
				newStat = player.getSpeed() + 1;
				player.setSpeed(newStat);
			}
			break;
			case 3:
			{
				spawner.Kill(i);
				newStat = player.getRange() + 1;
				player.setRange(newStat);
			}
			break;
			case 4:
			{
				spawner.Kill(i);
				player.setShots(2);
			}
			break;

			}

		}
	}
}



void Game::Run()
{
	gameover = false;
	playersTurn = true;

	spawner = Spawner();
	NonPlayerObj firstBug(1, board.getHorSq() / 2, 0);
	spawner.list().push_back(firstBug);
	player = Player();

	player.setPosX(board.getHorSq() / 2);
	player.setPosY(board.getVerSq() - 1);
	player.setFacing(0);
	

	Refresh();
	ReadKey();

	while (!ShouldClose()) {
		if (!isGameover()) {
			if (isPlayersTurn()) {
				PlayerMove();
			}
			else if (isEnemyTurn()) {
				MoveAllEnemies();
				
			}
			else {
				SpawnNewObjects();
			}
		}

	}
	CloseGraph();
}

	


	

void Game::PlayerMove()
{
	int moves = player.getSpeed();
	int shots = player.getShots();

	while (moves > 0 || shots > 0) {
		if (KeyPressed()) {
			Delay(50);

			// Go forward
			if (IsKeyPressed(87) && moves > 0) {
				Delay(50);
				printf("Going forward!\n");
				int f = player.getFacing();
				if (f == 0) {
					if (player.getPosY() > 0) {
						player.setPosY((player.getPosY() - 1));
					}
				}
				else if (f == 2) {
					if (player.getPosY() < board.getVerSq() - 1) {
						player.setPosY((player.getPosY() + 1));
					}
				}
				else if (f == 1) {
					if (player.getPosX() > 0) {
						player.setPosX((player.getPosX() - 1));
					}
				}
				else if (f == 3) {
					if (player.getPosX() < board.getHorSq()) {
						player.setPosX((player.getPosX() + 1));
					}
				}

				// Check for stomping
				CheckForStomp(player.getPosX(), player.getPosY());

				moves--;
				Refresh();
				ReadKey();
			}

			// Turn left
			if (IsKeyPressed(65) && moves > 0) {
				Delay(50);
				player.turnLeft();
				printf("Turning left\n");
				moves--;
				Refresh();
				ReadKey();
			}

			// Turn right
			if (IsKeyPressed(68) && moves > 0) {
				Delay(50);
				player.turnRight();
				printf("Turning right\n");
				moves--;
				Refresh();
				ReadKey();
			}

			// End turn
			if (IsKeyPressed(69)) {
				Delay(50);
				shots = 0;
				moves = 0;
			}


			// Shoot
			if (IsKeyPressed(70) && shots > 0) {
				Delay(50);
				Refresh();
				Image laserBase;
				Image laserTop;
				printf("Shooting!\n");

				if (!laserBase.LoadPNG("laser base.png"))
				{
					throw std::exception("Failed to load image");
				}
				if (!laserTop.LoadPNG("laser top.png"))
				{
					throw std::exception("Failed to load image");
				}

				int shootLength = player.getRange();
				int shiftX = 0;
				int shiftY = 0;
				int f = player.getFacing();
				if (f == 0) {
					shiftY = -1;
				}
				if (f == 1) {
					shiftX = -1;
				}
				if (f == 2) {
					shiftY = 1;
				}
				if (f == 3) {
					shiftX = 1;
				}


				while (shootLength > 1) {
					int x = (player.getPosX() + 0.5 + shiftX) * board.getTileSize();
					int y = (player.getPosY() + 0.5 + shiftY) * board.getTileSize();
					laserBase.DrawTilted(x, y, board.getTileSize(), board.getTileSize(), player.getFacing() * 90);
					//Check for kill
					CheckForKill(player.getPosX() + shiftX, player.getPosY() + shiftY);
					if (f == 0) {
						shiftY += -1;
					}
					if (f == 1) {
						shiftX += -1;
					}
					if (f == 2) {
						shiftY += 1;
					}
					if (f == 3) {
						shiftX += 1;
					}

					shootLength--;

				

				}
		

				laserTop.DrawTilted((player.getPosX() + 0.5 + shiftX) * board.getTileSize(),
					(player.getPosY() + 0.5 + shiftY) * board.getTileSize(),
					board.getTileSize(), board.getTileSize(),
					player.getFacing() * 90);

				CheckForKill(player.getPosX() + shiftX, player.getPosY() + shiftY);

				SwapBuffers();
				Delay(450);
				if (player.getPosY() + shiftY + 1 > board.getVerSq()) {
					setGameOver(true);
					GameOver();
				}
				else {
					shots--;
					Refresh();
					ReadKey();
				}

			}
		}


	}
	setPlayersTurn(false);
	setEnemyTurn(true);
}

