#pragma once

#include "BoardElement.h"
#include "BoardPoint.h"

#include <vector>
#include <string>

class GameBoard
{
public:
	GameBoard(std::string::const_iterator begin, std::string::const_iterator end);

	const BoardPoint& getMyPosition() const;
	bool isGameOver() const;
	bool hasElementAt(const BoardPoint& point, BoardElement element) const;
	BoardElement getElementAt(const BoardPoint& point) const;
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
	bool isNearToElement(const BoardPoint& point, BoardElement element) const;
	bool hasEnemyAt(const BoardPoint& point) const;
	bool hasOtherHeroAt(const BoardPoint& point) const;
	bool hasWallAt(const BoardPoint& point) const;
	bool hasLadderAt(const BoardPoint& point) const;
	bool hasGoldAt(const BoardPoint& point) const;
	bool hasPipeAt(const BoardPoint& point) const;
	bool hasShadowAt(const BoardPoint& point) const;

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