#include "BoardPoint.h"
#include <iostream>

BoardPoint::BoardPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}
BoardPoint::~BoardPoint() {

}
BoardPoint BoardPoint::shiftLeft(int delta)
{
	return BoardPoint(x - 1, y);
}

BoardPoint BoardPoint::shiftLeft() {
	return shiftLeft(1);
}
BoardPoint BoardPoint::shiftRight(int delta) {
	return BoardPoint(x + delta, y);
}
BoardPoint BoardPoint::shiftRight() {
	return shiftRight(1);
}
BoardPoint BoardPoint::shiftBottom(int delta) {
	return BoardPoint(x, y + delta);
}
BoardPoint BoardPoint::shiftBottom() {
	return shiftBottom(1);
}
BoardPoint BoardPoint::shiftTop(int delta) {
	return BoardPoint(x, y - delta);
}
BoardPoint BoardPoint::shiftTop() {
	return shiftTop(1);
}
int BoardPoint::getX() {
	return this->x;
}
int BoardPoint::getY() {
	return this->y;
}
bool BoardPoint::isOutOfBoard(int size) {
	return x >= size || y >= size || x < 0 || y < 0;
}

void BoardPoint::print() {
	std::cout << "[" << x << "," << y << "]" << "\n";
}
