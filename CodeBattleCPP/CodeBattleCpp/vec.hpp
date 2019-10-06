#pragma once
#include <cmath>

class vec
{
public:
	vec() : x(0), y(0) {}
	vec(int x, int y);
	~vec();

	vec shiftLeft(int delta);
	vec shiftLeft();
	vec shiftRight(int delta);
	vec shiftRight();
	vec shiftBottom(int delta);
	vec shiftBottom();
	vec shiftTop(int delta);
	vec shiftTop();
	bool isOutOfBoard(int size);
	void print();
	float dist_to(const vec& to) {	return std::sqrtf(std::powf(x - to.x, 2) + std::powf(y - to.y, 2)); }
	int x;
	int y;
};

static bool operator==(const vec& lhs, const vec& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

static bool operator!=(const vec& lhs, const vec& rhs) {
	return lhs.x != rhs.x || lhs.y != rhs.y;
}