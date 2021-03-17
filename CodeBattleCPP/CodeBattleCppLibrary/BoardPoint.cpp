#include "BoardPoint.h"
#include <iostream>

BoardPoint::BoardPoint(int x, int y) : x(x), y(y) {
}

BoardPoint BoardPoint::shiftLeft(int delta) const noexcept {
	return BoardPoint(x - delta, y);
}

BoardPoint BoardPoint::shiftLeft() const noexcept {
	return shiftLeft(1);
}

BoardPoint BoardPoint::shiftRight(int delta) const noexcept {
	return BoardPoint(x + delta, y);
}

BoardPoint BoardPoint::shiftRight() const noexcept {
	return shiftRight(1);
}

BoardPoint BoardPoint::shiftBottom(int delta) const noexcept {
	return BoardPoint(x, y + delta);
}

BoardPoint BoardPoint::shiftBottom() const noexcept {
	return shiftBottom(1);
}

BoardPoint BoardPoint::shiftTop(int delta) const noexcept {
	return BoardPoint(x, y - delta);
}

BoardPoint BoardPoint::shiftTop() const noexcept {
	return shiftTop(1);
}

int BoardPoint::getX() const noexcept {
	return this->x;
}

int BoardPoint::getY() const noexcept {
	return this->y;
}

bool BoardPoint::isOutOfBoard(int size) const noexcept {
	return x >= size || y >= size || x < 0 || y < 0;
}

void BoardPoint::print() const noexcept {
	std::cout << "[" << x << "," << y << "]" << "\n";
}

bool operator==(const BoardPoint& p1, const BoardPoint& p2) {
	return ((p1.getX() == p2.getX()) && (p1.getY() == p2.getY()));
}