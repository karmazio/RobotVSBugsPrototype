#include "Board.h"
#include "glfwbgi.h"

using namespace Graph;

Board::Board()
{
	horSq = 0;
	verSq = 0;
}

Board::Board(int h, int v)
{
	horSq = h;
	verSq = v;
}

void Board::setHorSq(int h)
{
	horSq = h;
}

void Board::setVerSq(int v)
{
	verSq = v;
}

void Board::setTileSize(int ts)
{
	tileSize = ts;
}

int Board::getHorSq()
{
	return horSq;
}

int Board::getVerSq()
{
	return verSq;
}

int Board::getTileSize()
{
	return tileSize;
}

void Board::Draw(int screenW, int screenH)
{
	for (int i = 0; i < verSq; i++) {
		for (int k = 0; k < horSq; k++) {
			int x1 = k * tileSize;
			int y1 = i * tileSize;
			int x2 = (k + 1) * tileSize;
			int y2 = (i + 1) * tileSize;

			FillRectangle(x1, y1, x2, y2, Color::DodgerBlue);
			FillRectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3, Color::Black);
			
		/*	printf("%d, %d\n", i, k);*/
		}
	}
	Image skyline;
	if (!skyline.LoadPNG("skyline.png"))
	{
		throw std::exception("Failed to load image");
	}
	for (int i = 0; i < horSq; i++) {
		skyline.DrawTilted((i + 0.5) * tileSize, (verSq + 0.5) * tileSize, tileSize, tileSize, 0);
	}
}

