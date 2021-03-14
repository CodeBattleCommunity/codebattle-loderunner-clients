#include <iostream>
#include <random>

#include "GameClientLodeRunner.h"

int main()
{
	srand(static_cast<uint32_t>(time(0)));

	const std::string serverUrl = "http://codebattle2021.westeurope.cloudapp.azure.com/codenjoy-contest/board/player/8tpxg3ohy8saq6lge9dq?code=5120724914036517902&gameName=loderunner";

	GameClientLodeRunner gcb(serverUrl);
	gcb.Run([&]()
	{
			const auto& gb = gcb.get_GameBoard();
			const auto& gold = gb.getGoldPositions();

			bool done = false;
			switch (rand() % 5)
			{
			case 0: gcb.LoderunnerAction(LoderunnerAction::GO_UP); done = true; break;
			case 1: gcb.LoderunnerAction(LoderunnerAction::GO_DOWN); done = true; break;
			case 2: gcb.LoderunnerAction(LoderunnerAction::GO_LEFT); done = true; break;
			case 3: gcb.LoderunnerAction(LoderunnerAction::GO_RIGHT); done = true; break;
			case 4: gcb.LoderunnerAction(LoderunnerAction::DRILL); done = true; break;
			}
			if (!done) {
				gcb.LoderunnerAction(LoderunnerAction::DO_NOTHING);
			}
	});

	getchar();

	return 0;
}
