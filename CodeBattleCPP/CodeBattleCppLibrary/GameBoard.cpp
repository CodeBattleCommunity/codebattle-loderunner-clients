#include "GameBoard.h"

GameBoard::GameBoard(BoardElement** map, int map_size)
{
	this->map = map;
	this->map_size = map_size;
}
BoardPoint GameBoard::getMyPosition() {
	std::list<BoardPoint> result = findAllElements(BoardElement::HERO_DIE);
	result.splice(result.end(), findAllElements(BoardElement::HERO_DRILL_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_DRILL_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_LADDER));
	result.splice(result.end(), findAllElements(BoardElement::HERO_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_FALL_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_FALL_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_PIPE_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_PIPE_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_DRILL_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_DRILL_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_LADDER));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_FALL_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_FALL_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_PIPE_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_SHADOW_PIPE_RIGHT));
	return result.front();
}
bool GameBoard::isGameOver() {
	for (uint32_t j = 0; j < map_size; j++)
	{
		for (uint32_t i = 0; i < map_size; i++)
		{
			if (map[j][i] == BoardElement::HERO_DIE) {
				return true;
			}
		}
	}
	return false;
}
bool GameBoard::hasElementAt(BoardPoint point, BoardElement element) {
	if (point.isOutOfBoard(map_size)) {
		return false;
	}
	return getElementAt(point) == element;
}
BoardElement GameBoard::getElementAt(BoardPoint point) {
	return map[point.getX()][point.getY()];
}
std::list<BoardPoint> GameBoard::findAllElements(BoardElement element) {
	std::list<BoardPoint> result;
	for (uint32_t j = 0; j < map_size; j++)
	{
		for (uint32_t i = 0; i < map_size; i++)
		{
			if (map[j][i] == element) {
				result.push_back(BoardPoint(j, i));
			}
		}
	}
	return result;
}
std::list<BoardPoint> GameBoard::getOtherHeroPositions() {
	std::list<BoardPoint> result = findAllElements(BoardElement::OTHER_HERO_DIE);
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_LADDER));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_PIPE_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_PIPE_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_SHADOW_DIE));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_SHADOW_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_SHADOW_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_SHADOW_LADDER));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_SHADOW_PIPE_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_SHADOW_PIPE_RIGHT));
	return result;
}
std::list<BoardPoint> GameBoard::getWallPositions() {
	std::list<BoardPoint> result = findAllElements(BoardElement::BRICK);
	result.splice(result.end(), findAllElements(BoardElement::UNDESTROYABLE_WALL));
	return result;
}
std::list<BoardPoint> GameBoard::getLadderPositions() {
	std::list<BoardPoint> result = findAllElements(BoardElement::LADDER);
	result.splice(result.end(), findAllElements(BoardElement::HERO_LADDER));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_LADDER));
	result.splice(result.end(), findAllElements(BoardElement::ENEMY_LADDER));
	return result;
}
std::list<BoardPoint> GameBoard::getGoldPositions() {
	std::list<BoardPoint> result = findAllElements(BoardElement::YELLOW_GOLD);
	result.splice(result.end(), findAllElements(BoardElement::GREEN_GOLD));
	result.splice(result.end(), findAllElements(BoardElement::RED_GOLD));
	return result;
}
std::list<BoardPoint> GameBoard::getPipePositions() {
	std::list<BoardPoint> result = findAllElements(BoardElement::PIPE);
	result.splice(result.end(), findAllElements(BoardElement::HERO_PIPE_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::HERO_PIPE_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_PIPE_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::OTHER_HERO_PIPE_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::ENEMY_PIPE_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::ENEMY_PIPE_RIGHT));
	return result;
}
std::list<BoardPoint> GameBoard::getEnemyPositions() {
	std::list<BoardPoint> result = findAllElements(BoardElement::ENEMY_LADDER);
	result.splice(result.end(), findAllElements(BoardElement::ENEMY_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::ENEMY_PIPE_LEFT));
	result.splice(result.end(), findAllElements(BoardElement::ENEMY_PIPE_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::ENEMY_RIGHT));
	result.splice(result.end(), findAllElements(BoardElement::ENEMY_PIT));
	return result;
}
std::list<BoardPoint> GameBoard::getPortals() {
	return findAllElements(BoardElement::PORTAL);
}

std::list<BoardPoint> GameBoard::getShadowPills() {
	return findAllElements(BoardElement::THE_SHADOW_PILL);
}
bool GameBoard::isNearToElement(BoardPoint point, BoardElement element) {
	if (point.isOutOfBoard(map_size)) {
		return false;
	}
	return hasElementAt(point.shiftBottom(), element)
		|| hasElementAt(point.shiftTop(), element)
		|| hasElementAt(point.shiftLeft(), element)
		|| hasElementAt(point.shiftRight(), element);
}
bool GameBoard::hasEnemyAt(BoardPoint point) {
	std::list<BoardPoint> enemies = getEnemyPositions();
	for (std::list<BoardPoint>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}
bool GameBoard::hasOtherHeroAt(BoardPoint point) {
	std::list<BoardPoint> enemies = getOtherHeroPositions();
	for (std::list<BoardPoint>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}
bool GameBoard::hasWallAt(BoardPoint point) {
	std::list<BoardPoint> enemies = getWallPositions();
	for (std::list<BoardPoint>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}
bool GameBoard::hasLadderAt(BoardPoint point) {
	std::list<BoardPoint> enemies = getLadderPositions();
	for (std::list<BoardPoint>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}
bool GameBoard::hasGoldAt(BoardPoint point) {
	std::list<BoardPoint> enemies = getGoldPositions();
	for (std::list<BoardPoint>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}
bool GameBoard::hasPipeAt(BoardPoint point) {
	std::list<BoardPoint> enemies = getPipePositions();
	for (std::list<BoardPoint>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}

bool GameBoard::hasShadowAt(BoardPoint point) {
	std::list<BoardPoint> enemies = getShadowPills();
	for (std::list<BoardPoint>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if (it->getX() == point.getX() && it->getY() == point.getY()) {
			return true;
		}
	}
	return false;
}
GameBoard::~GameBoard()
{
	delete map;
}

