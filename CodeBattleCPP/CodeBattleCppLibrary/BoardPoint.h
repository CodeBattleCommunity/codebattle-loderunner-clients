#pragma once

class BoardPoint
{
public:
	BoardPoint(int x, int y);

	BoardPoint shiftLeft(int delta) const noexcept;
	BoardPoint shiftLeft() const noexcept;

	BoardPoint shiftRight(int delta) const noexcept;
	BoardPoint shiftRight() const noexcept;

	BoardPoint shiftBottom(int delta) const noexcept;
	BoardPoint shiftBottom() const noexcept;

	BoardPoint shiftTop(int delta) const noexcept;
	BoardPoint shiftTop() const noexcept;

	int getX() const noexcept;
	int getY() const noexcept;

	bool isOutOfBoard(int size) const noexcept;
	void print() const noexcept;

private:
	int x;
	int y;
};

bool operator==(const BoardPoint& p1, const BoardPoint& p2);