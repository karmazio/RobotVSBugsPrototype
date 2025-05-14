#pragma once
class Board
{
private:
	int horSq;
	int verSq;
	int tileSize;
public:
	Board();
	Board(int h, int v);
	void setHorSq(int h);
	void setVerSq(int v);
	void setTileSize(int ts);

	int getHorSq();
	int getVerSq();
	int getTileSize();

	void Draw(int screenW, int screenH);
};