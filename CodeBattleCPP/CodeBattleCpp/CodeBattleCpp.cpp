#include <iostream>
#include <random>

#include "GameClientLodeRunner.h"

	/*
	 !!!!!ВНИМАНИЕ!!!!!
		Запускать приложение только в Microsoft Visual Studio 2017
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
	 
	 Прописываем их так:
		GameClientLodeRunner *gcb = new GameClientLodeRunner("localhost:8888", "cg601yim3186cotnftue", "8887669793631271133")
	*/
	GameClientLodeRunner *gcb = new GameClientLodeRunner("адрес сервера", "id пользователя", "код пользователя");
	gcb->Run([&]()
	{
		LodeRunnerBlocks **map = gcb->get_map();
		/*
		 пишем код здесь 
		 список комманд
			 gcb->Blank() - ничего не делать
			 gcb->Act() - сверлить дыру
			 gcb->get_map() - получить карту
			 Комманды движения:
			 gcb->Up() 
			 gcb->Down()
			 gcb->Left()
			 gcb->Right()
			 Если нужно сделать движение и просверлить дырку т.е. комманды типа (LEFT, ACT), то вызываем методы так
			 gcb->Up(PlayerAction::ACT)
			 gcb->Down(PlayerAction::ACT)
			 gcb->Left(PlayerAction::ACT)
			 gcb->Right(PlayerAction::ACT)
			 по дефолту в методе стоит PlayerAction::None

			 Циклы здесь писать не нужно т.к. тут возможно отправить только одну комманду боту за шаг.
			 При вызове методов Up(), Down(), Left(), Right(), Act() идёт сразу отправка комманды на сервер.
			 После этого происходит расчёт хода на сервере и он(сервер) отправляет новое состояние поля т.е.
			 мы пишем код в цикле. 

		*/

		bool done = false;

		switch (rand() % 5)
		{
			case 0: gcb->Up(PlayerAction::ACT); done = true;
			case 1: gcb->Down(PlayerAction::ACT); done = true;
			case 2: gcb->Left(PlayerAction::ACT); done = true;
			case 3: gcb->Right(PlayerAction::ACT); done = true;
			case 4: gcb->Act(); done = true;
		}


		if (done == false)
			gcb->Blank();
	});

	getchar();
}
