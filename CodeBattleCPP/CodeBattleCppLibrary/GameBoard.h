#pragma once

#include "BoardElement.h"
#include "BoardPoint.h"
#include <list>

class GameBoard
{
public:
	GameBoard(BoardElement** map, int map_size);
	BoardPoint getMyPosition();
	bool isGameOver();
	bool hasElementAt(BoardPoint point, BoardElement element);
	BoardElement getElementAt(BoardPoint point);
	//void printBoard();
	std::list<BoardPoint> findAllElements(BoardElement element);
	std::list<BoardPoint> getOtherHeroPositions();
	std::list<BoardPoint> getWallPositions();
	std::list<BoardPoint> getLadderPositions();
	std::list<BoardPoint> getGoldPositions();
	std::list<BoardPoint> getPipePositions();
	std::list<BoardPoint> getEnemyPositions();
	std::list<BoardPoint> getPortals();
	std::list<BoardPoint> getShadowPills();
	bool isNearToElement(BoardPoint point, BoardElement element);
	bool hasEnemyAt(BoardPoint point);
	bool hasOtherHeroAt(BoardPoint point);
	bool hasWallAt(BoardPoint point);
	bool hasLadderAt(BoardPoint point);
	bool hasGoldAt(BoardPoint point);
	bool hasPipeAt(BoardPoint point);
	bool hasShadowAt(BoardPoint point);
	~GameBoard();

private:
	BoardElement** map;
	int map_size;
};