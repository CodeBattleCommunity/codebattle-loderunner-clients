#include <iostream>
#include <random>

#include "GameClientLodeRunner.h"

	/*
		Если при сборке появилась ошибка типа 
		The Windows SDK version 10.0.16299.0 was not found...
		делаем следующее:
			1)Правой кнопкой мыши по CodeBattleCpp и жмём на properties.
			2)Вкладка Configuration Properties->General
			3)Находим Windows SDK Version и берем доступную в выпадающем списке
			4)Нажимаем Apply
			5)Повторяем тоже самое с CodeBattleCppLibrary
	*/


void main()
{
	srand(time(0));
	/*
	 После регистрации вас переведёт на страницу с картой и списком игроков.
	 URL будет примерно такой: http://localhost:8888/codenjoy-contest/board/player/cg601yim3186cotnftue?code=8887669793631271133&gameName=loderunner
	 из url берём:
	 адрес сервера = localhost:8888
	 id пользователя = cg601yim3186cotnftue
	 код пользователя = 8887669793631271133
	*/
	std::string url = "localhost:8888";
	std::string userId = "cg601yim3186cotnftue";
	std::string userCode = "8887669793631271133";
	GameClientLodeRunner *gcb = new GameClientLodeRunner(url, userId, userCode);
	gcb->Run([&]()
	{
			GameBoard* gb = gcb->get_GameBoard();
			std::list<BoardPoint> gold = gb->getGoldPositions();

			bool done = false;
			switch (rand() % 5)
			{
				case 0: gcb->LoderunnerAction(LoderunnerAction::GO_UP); done = true;
				case 1: gcb->LoderunnerAction(LoderunnerAction::GO_DOWN); done = true;
				case 2: gcb->LoderunnerAction(LoderunnerAction::GO_LEFT); done = true;
				case 3: gcb->LoderunnerAction(LoderunnerAction::GO_RIGHT); done = true;
				case 4: gcb->LoderunnerAction(LoderunnerAction::DRILL); done = true;
			}
			if (!done) {
				gcb->LoderunnerAction(LoderunnerAction::DO_NOTHING);
			}
	});

	getchar();
}
