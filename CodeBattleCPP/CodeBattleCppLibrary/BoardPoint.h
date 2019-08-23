#pragma once

class BoardPoint
{
public:
	BoardPoint(int x, int y);
	~BoardPoint();

	BoardPoint shiftLeft(int delta);
	BoardPoint shiftLeft();
	BoardPoint shiftRight(int delta);
	BoardPoint shiftRight();
	BoardPoint shiftBottom(int delta);
	BoardPoint shiftBottom();
	BoardPoint shiftTop(int delta);
	BoardPoint shiftTop();
	int getX();
	int getY();
	bool isOutOfBoard(int size);
	void print();
private:
	int x;
	int y;
};