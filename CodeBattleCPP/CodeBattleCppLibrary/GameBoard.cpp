#include "GameBoard.h"
#include "utf8tools.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>

namespace
{
	bool isHero(BoardElement element) {
		switch (element) {
		case BoardElement::HERO_DIE:
		case BoardElement::HERO_DRILL_LEFT:
		case BoardElement::HERO_DRILL_RIGHT:
		case BoardElement::HERO_LADDER:
		case BoardElement::HERO_LEFT:
		case BoardElement::HERO_RIGHT:
		case BoardElement::HERO_FALL_LEFT:
		case BoardElement::HERO_FALL_RIGHT:
		case BoardElement::HERO_PIPE_LEFT:
		case BoardElement::HERO_PIPE_RIGHT:
		case BoardElement::HERO_SHADOW_DRILL_LEFT:
		case BoardElement::HERO_SHADOW_DRILL_RIGHT:
		case BoardElement::HERO_SHADOW_LADDER:
		case BoardElement::HERO_SHADOW_LEFT:
		case BoardElement::HERO_SHADOW_RIGHT:
		case BoardElement::HERO_SHADOW_FALL_LEFT:
		case BoardElement::HERO_SHADOW_FALL_RIGHT:
		case BoardElement::HERO_SHADOW_PIPE_LEFT:
		case BoardElement::HERO_SHADOW_PIPE_RIGHT:
			return true;
		default:
			return false;
		}
	}

	bool isOtherHero(BoardElement element) {
		switch (element) {
		case BoardElement::OTHER_HERO_RIGHT:
		case BoardElement::OTHER_HERO_LADDER:
		case BoardElement::OTHER_HERO_PIPE_LEFT:
		case BoardElement::OTHER_HERO_PIPE_RIGHT:
		case BoardElement::OTHER_HERO_SHADOW_DIE:
		case BoardElement::OTHER_HERO_SHADOW_LEFT:
		case BoardElement::OTHER_HERO_SHADOW_RIGHT:
		case BoardElement::OTHER_HERO_SHADOW_LADDER:
		case BoardElement::OTHER_HERO_SHADOW_PIPE_LEFT:
		case BoardElement::OTHER_HERO_SHADOW_PIPE_RIGHT:
			return true;
		default:
			return false;
		}
	}

	bool isWall(BoardElement element) {
		switch (element) {
		case BoardElement::BRICK:
		case BoardElement::INDESTRUCTIBLE_WALL:
			return true;
		default:
			return false;
		}
	}

	bool isLadder(BoardElement element) {
		switch (element) {
		case BoardElement::LADDER:
		case BoardElement::HERO_LADDER:
		case BoardElement::HERO_SHADOW_LADDER:
		case BoardElement::OTHER_HERO_LADDER:
		case BoardElement::OTHER_HERO_SHADOW_LADDER:
		case BoardElement::ENEMY_LADDER:
			return true;
		default:
			return false;
		}
	}

	bool isGold(BoardElement element) {
		switch (element) {
		case BoardElement::YELLOW_GOLD:
		case BoardElement::GREEN_GOLD:
		case BoardElement::RED_GOLD:
			return true;
		default:
			return false;
		}
	}

	bool isPipe(BoardElement element) {
		switch (element) {
		case BoardElement::PIPE:
		case BoardElement::HERO_PIPE_LEFT:
		case BoardElement::HERO_PIPE_RIGHT:
		case BoardElement::HERO_SHADOW_PIPE_LEFT:
		case BoardElement::HERO_SHADOW_PIPE_RIGHT:
		case BoardElement::OTHER_HERO_PIPE_LEFT:
		case BoardElement::OTHER_HERO_PIPE_RIGHT:
		case BoardElement::OTHER_HERO_SHADOW_PIPE_LEFT:
		case BoardElement::OTHER_HERO_SHADOW_PIPE_RIGHT:
		case BoardElement::ENEMY_PIPE_LEFT:
		case BoardElement::ENEMY_PIPE_RIGHT:
			return true;
		default:
			return false;
		}
	}

	bool isEnemy(BoardElement element) {
		switch (element) {
		case BoardElement::ENEMY_LADDER:
		case BoardElement::ENEMY_LEFT:
		case BoardElement::ENEMY_PIPE_LEFT:
		case BoardElement::ENEMY_PIPE_RIGHT:
		case BoardElement::ENEMY_RIGHT:
		case BoardElement::ENEMY_PIT:
			return true;
		default:
			return false;
		}
	}

	bool isPortal(BoardElement element) {
		return (element == BoardElement::PORTAL);
	}

	bool isPill(BoardElement element) {
		return (element == BoardElement::THE_SHADOW_PILL);
	}

} // namespace

GameBoard::GameBoard(std::string::const_iterator begin, std::string::const_iterator end)
	: m_myPosition(0,0)
{
	const auto messageSize = utf8_strlen(begin, end);
	int size = static_cast<int>(std::sqrt(messageSize));
	m_map.resize(size, std::vector<BoardElement>(size, BoardElement::NONE));

	auto it = begin;
	int row = 0, column = 0;
	while(it != end) {
		const auto next = utf8_next(it);
		const std::string token(it, next);
		const auto element = BoardElementFromString(token);
		m_map[row][column] = element;

		if (isHero(element)) {
			m_myPosition = std::move(BoardPoint(column, row));
		}

		if (isOtherHero(element)) {
			m_otherHeroPositions.emplace_back(BoardPoint(column, row));
		}

		if (isWall(element)) {
			m_wallPositions.emplace_back(BoardPoint(column, row));
		}

		if (isLadder(element)) {
			m_ladderPositions.emplace_back(BoardPoint(column, row));
		}

		if (isGold(element)) {
			m_goldPositions.emplace_back(BoardPoint(column, row));
		}

		if (isPipe(element)) {
			m_pipePositions.emplace_back(BoardPoint(column, row));
		}

		if (isEnemy(element)) {
			m_enemyPositions.emplace_back(BoardPoint(column, row));
		}

		if (isPortal(element)) {
			m_portalsPositions.emplace_back(BoardPoint(column, row));
		}

		if (isPill(element)) {
			m_pillsPositions.emplace_back(BoardPoint(column, row));
		}

		++column;
		if(column == size) {
			column = 0;
			++row;
		}

		it = next;
	}
}

void GameBoard::printBoard() const {
	for(const auto& columns : m_map) {
		for(const auto& column : columns) {
			std::cout << std::to_string(column);
		}
		std::cout << '\n';
	}
}

const BoardPoint& GameBoard::getMyPosition() const {
	return m_myPosition;
}

bool GameBoard::isGameOver() const {
	for(const auto& columns : m_map) {
		for(const auto& element : columns) {
			if(element == BoardElement::HERO_DIE) {
				return true;
			}
		}
	}

	return false;
}

bool GameBoard::hasElementAt(const BoardPoint& point, BoardElement element) const {
	if (point.isOutOfBoard(static_cast<int>(m_map.size()))) {
		return false;
	}
	return getElementAt(point) == element;
}

BoardElement GameBoard::getElementAt(const BoardPoint& point) const {
	return m_map[point.getY()][point.getX()];
}

std::vector<BoardPoint> GameBoard::findAllElements(BoardElement element) const {
	std::vector<BoardPoint> result;
	for (size_t j = 0; j < m_map.size(); j++) {
		for (size_t i = 0; i < m_map.size(); i++) {
			if (m_map[j][i] == element) {
				result.push_back(BoardPoint(static_cast<int>(i), static_cast<int>(j)));
			}
		}
	}
	return result;
}

const std::vector<BoardPoint>& GameBoard::getOtherHeroPositions() const {
	return m_otherHeroPositions;
}

const std::vector<BoardPoint>& GameBoard::getWallPositions() const {
	return m_wallPositions;
}

const std::vector<BoardPoint>& GameBoard::getLadderPositions() const {
	return m_ladderPositions;
}

const std::vector<BoardPoint>& GameBoard::getGoldPositions() const {
	return m_goldPositions;
}

const std::vector<BoardPoint>& GameBoard::getPipePositions() const {
	return m_pipePositions;
}

const std::vector<BoardPoint>& GameBoard::getEnemyPositions() const {
	return m_enemyPositions;
}

const std::vector<BoardPoint>& GameBoard::getPortals() const {
	return m_portalsPositions;
}

const std::vector<BoardPoint>& GameBoard::getShadowPills() const {
	return m_pillsPositions;
}
bool GameBoard::isNearToElement(const BoardPoint& point, BoardElement element) const {
	if (point.isOutOfBoard(static_cast<int>(m_map.size()))) {
		return false;
	}
	return hasElementAt(point.shiftBottom(), element)
		|| hasElementAt(point.shiftTop(), element)
		|| hasElementAt(point.shiftLeft(), element)
		|| hasElementAt(point.shiftRight(), element);
}

bool GameBoard::hasEnemyAt(const BoardPoint& point) const {
	const auto& enemies = getEnemyPositions();
	for (auto it = enemies.cbegin(); it != enemies.cend(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}

bool GameBoard::hasOtherHeroAt(const BoardPoint& point) const {
	const auto& enemies = getOtherHeroPositions();
	for (auto it = enemies.cbegin(); it != enemies.cend(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}

bool GameBoard::hasWallAt(const BoardPoint& point) const {
	const auto& enemies = getWallPositions();
	for (auto it = enemies.cbegin(); it != enemies.cend(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}

bool GameBoard::hasLadderAt(const BoardPoint& point) const {
	const auto& enemies = getLadderPositions();
	for (auto it = enemies.cbegin(); it != enemies.cend(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}

bool GameBoard::hasGoldAt(const BoardPoint& point) const {
	const auto& enemies = getGoldPositions();
	for (auto it = enemies.cbegin(); it != enemies.cend(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}

bool GameBoard::hasPipeAt(const BoardPoint& point) const {
	const auto& enemies = getPipePositions();
	for (auto it = enemies.cbegin(); it != enemies.cend(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}

bool GameBoard::hasShadowAt(const BoardPoint& point) const {
	const auto& enemies = getShadowPills();
	for (auto it = enemies.cbegin(); it != enemies.cend(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}

size_t GameBoard::getBoardSize() const {
	return m_map.size();
}