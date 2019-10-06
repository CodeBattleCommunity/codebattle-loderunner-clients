#include "vec.hpp"
#include <iostream>

vec::vec(int x, int y)
{
	this->x = x;
	this->y = y;
}
vec::~vec() {

}
vec vec::shiftLeft(int delta)
{
	return vec(x - 1, y);
}

vec vec::shiftLeft() {
	return shiftLeft(1);
}
vec vec::shiftRight(int delta) {
	return vec(x + delta, y);
}
vec vec::shiftRight() {
	return shiftRight(1);
}
vec vec::shiftBottom(int delta) {
	return vec(x, y + delta);
}
vec vec::shiftBottom() {
	return shiftBottom(1);
}
vec vec::shiftTop(int delta) {
	return vec(x, y - delta);
}
vec vec::shiftTop() {
	return shiftTop(1);
}

bool vec::isOutOfBoard(int size) {
	return x >= size || y >= size || x < 0 || y < 0;
}

void vec::print() {
	std::cout << "[" << x << "," << y << "]" << "\n";
}
