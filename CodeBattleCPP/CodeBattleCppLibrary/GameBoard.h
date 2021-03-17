#pragma once

#include "BoardElement.h"
#include "BoardPoint.h"

#include <vector>
#include <string>

class GameBoard
{
public:
	GameBoard(std::string::const_iterator begin, std::string::const_iterator end);
	GameBoard();

	const BoardPoint& getMyPosition() const;
	bool isGameOver() const;
	bool hasElementAt(BoardPoint point, BoardElement element) const;
	BoardElement getElementAt(BoardPoint point) const;
	void printBoard() const;
	std::vector<BoardPoint> findAllElements(BoardElement element) const;
	const std::vector<BoardPoint>& getOtherHeroPositions() const;
	const std::vector<BoardPoint>& getWallPositions() const;
	const std::vector<BoardPoint>& getLadderPositions() const;
	const std::vector<BoardPoint>& getGoldPositions() const;
	const std::vector<BoardPoint>& getPipePositions() const;
	const std::vector<BoardPoint>& getEnemyPositions() const;
	const std::vector<BoardPoint>& getPortals() const;
	const std::vector<BoardPoint>& getShadowPills() const;
	bool isNearToElement(BoardPoint point, BoardElement element) const;
	bool hasEnemyAt(BoardPoint point) const;
	bool hasOtherHeroAt(BoardPoint point) const;
	bool hasWallAt(BoardPoint point) const;
	bool hasLadderAt(BoardPoint point) const;
	bool hasGoldAt(BoardPoint point) const;
	bool hasPipeAt(BoardPoint point) const;
	bool hasShadowAt(BoardPoint point) const;

private:
	std::vector<std::vector<BoardElement>> m_map;
	std::vector<BoardPoint> m_otherHeroPositions;
	std::vector<BoardPoint> m_wallPositions;
	std::vector<BoardPoint> m_goldPositions;
	std::vector<BoardPoint> m_ladderPositions;
	std::vector<BoardPoint> m_pipePositions;
	std::vector<BoardPoint> m_enemyPositions;
	std::vector<BoardPoint> m_portalsPositions;
	std::vector<BoardPoint> m_pillsPositions;
	BoardPoint m_myPosition;
};