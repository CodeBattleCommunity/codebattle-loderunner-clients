#include <iostream>
#include <random>

#include "GameClientLodeRunner.h"
#include "GameBoard.h"

LodeRunnerAction makeTurn(const GameBoard& board) {
	const BoardPoint& position = board.getMyPosition();
	std::cout << "Hero position is (" << position.getX() << "," << position.getY() << ")\n";

	switch (rand() % 5)
	{
	case 0:
		return LodeRunnerAction::GO_UP;
	case 1:
		return LodeRunnerAction::GO_DOWN;
	case 2:
		return LodeRunnerAction::GO_LEFT;
	case 3:
		return LodeRunnerAction::GO_RIGHT;
	case 4:
		return LodeRunnerAction::DRILL;
	}
}

int main() {
	const std::string serverUrl = "<put your URL here>";

	GameClientLodeRunner gcb(serverUrl);
	gcb.Run(makeTurn);

	return 0;
}
