# C++ клиент для игры LodeRunner
## Требования:
* компилятор с поддержкой стандарта языка C++11
  * Visual Studio 2015 или новее
  * GCC 4.8 или новее
  * clang 3.3 или новее
* cmake 3.0.0 или новее

## Сборка проекта:
### Из консоли:
* Переходим в каталог с кодом клиента
```
C:\codebattle-loderunner-clients>cd CodeBattleCPP
```
* Создадим новый каталог, в котором будет происходить сборка проекта
```
C:\codebattle-loderunner-clients\CodeBattleCPP>mkdir build
```
* Сконфигурируем проект
```
C:\codebattle-loderunner-clients\CodeBattleCPP>cmake -S . -B build
-- Building for: Visual Studio 16 2019
-- Selecting Windows SDK version 10.0.18362.0 to target Windows 10.0.18363.
-- The CXX compiler identification is MSVC 19.28.29336.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Tools/MSVC/14.28.29333/bin/Hostx64/x64/cl.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: C:/codebattle-loderunner-clients/CodeBattleCPP/build
```

Параметр `-S` указывает на каталог, в котором находится CMakeLists.txt. В нашем случае данный файл находится в том же каталоге, из которого мы запускаем данную команду

Параметр `-B` указывает на каталог, в котором будет происходить сборка

При необходимости сгенерировать конкретный типа проекта, нужно указать параметр `-G`. Список поддерживаемых генераторов проектов выглядит следующим образом:
```
Generators
* Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 11 2012 [arch] = Generates Visual Studio 2012 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 10 2010 [arch] = Generates Visual Studio 2010 project files.
                                 Optional [arch] can be "Win64" or "IA64".
  Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files.
                                 Optional [arch] can be "Win64" or "IA64".
  Borland Makefiles            = Generates Borland makefiles.
  NMake Makefiles              = Generates NMake makefiles.
  NMake Makefiles JOM          = Generates JOM makefiles.
  MSYS Makefiles               = Generates MSYS makefiles.
  MinGW Makefiles              = Generates a make file for use with
                                 mingw32-make.
  Unix Makefiles               = Generates standard UNIX makefiles.
  Green Hills MULTI            = Generates Green Hills MULTI files
                                 (experimental, work-in-progress).
  Ninja                        = Generates build.ninja files.
  Ninja Multi-Config           = Generates build-<Config>.ninja files.
  Watcom WMake                 = Generates Watcom WMake makefiles.
  CodeBlocks - MinGW Makefiles = Generates CodeBlocks project files.
  CodeBlocks - NMake Makefiles = Generates CodeBlocks project files.
  CodeBlocks - NMake Makefiles JOM
                               = Generates CodeBlocks project files.
  CodeBlocks - Ninja           = Generates CodeBlocks project files.
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
  CodeLite - MinGW Makefiles   = Generates CodeLite project files.
  CodeLite - NMake Makefiles   = Generates CodeLite project files.
  CodeLite - Ninja             = Generates CodeLite project files.
  CodeLite - Unix Makefiles    = Generates CodeLite project files.
  Sublime Text 2 - MinGW Makefiles
                               = Generates Sublime Text 2 project files.
  Sublime Text 2 - NMake Makefiles
                               = Generates Sublime Text 2 project files.
  Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files.
  Sublime Text 2 - Unix Makefiles
                               = Generates Sublime Text 2 project files.
  Kate - MinGW Makefiles       = Generates Kate project files.
  Kate - NMake Makefiles       = Generates Kate project files.
  Kate - Ninja                 = Generates Kate project files.
  Kate - Unix Makefiles        = Generates Kate project files.
  Eclipse CDT4 - NMake Makefiles
                               = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - MinGW Makefiles
                               = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files.
```
* Соберем сгенерированный проект
```
C:\codebattle-loderunner-clients\CodeBattleCPP>cmake --build build
Microsoft (R) Build Engine version 16.8.3+39993bd9d for .NET Framework
Copyright (C) Microsoft Corporation. All rights reserved.

  Checking Build System
  Building Custom Rule C:/codebattle-loderunner-clients/CodeBattleCPP/CodeBattleCppLibrary/easywsclient/CMakeLists.txt
  easywsclient.cpp
  easywsclient.vcxproj -> C:\codebattle-loderunner-clients\CodeBattleCPP\build
  \CodeBattleCppLibrary\easywsclient\Debug\easywsclient.lib
  Building Custom Rule C:/codebattle-loderunner-clients/CodeBattleCPP/CodeBattleCppLibrary/CMakeLists.txt
  BoardElement.cpp
  BoardPoint.cpp
  GameBoard.cpp
  GameClientLodeRunner.cpp
  LodeRunnerAction.cpp
  Generating Code...
  loderunner-client-library.vcxproj -> C:\codebattle-loderunner-clients\CodeBattleCPP\build\CodeBattleCppLibrary\Debug\loderunner-client-library.lib
  Building Custom Rule C:/codebattle-loderunner-clients/CodeBattleCPP/CMakeLists.txt
  CodeBattleCpp.cpp
  loderunner-client.vcxproj -> C:\codebattle-loderunner-clients\CodeBattleCPP\build\Debug\loderunner-client.exe
  Building Custom Rule C:/codebattle-loderunner-clients/CodeBattleCPP/CMakeLists.txt
```
* Запустим собранный исполняемый файл
```
C:\codebattle-loderunner-clients\CodeBattleCPP>build\Debug\loderunner-client.exe
```
Если при конфигурации проекта вы явно указали собрать релизную конфигурацию, то в команде выше нужно заменить `Debug` на `Release`

Для остановки клиента необходимо нажать `Ctrl+C`

### Из среды разработки
* Visual Studio - современные версии данной IDE имеют встроенную поддержку cmake проектов, поэтому вам достаточно лишь открыть каталог с файлом CMakeLists.txt и дальше вы сможете работать с данным проектам также, как и с любым другим проектом для Visual Studio.
* VS Code - при открытии каталога с файлом CMakeLists.txt предложит установить расширении для работы с cmake проектами, который автоматизирует конфигурацию проекта и упростит работу с ним в целом. Если вы раньше не использовали данное расширение, ознакомьтесь с документацией к нему.
* Другие IDE - ознакомьтесь с документацией к вашей IDE на предмет интеграции с cmake или поищите информацию в сети Интернет
## Модификация проекта
Все файлы из каталога `CodeBattleCppLibrary` являются служебными и НЕ должны быть модифицированы вами. Они лишь скрывают детали подключения к серверу, разбор сообщений от него и отправку ответов. Единственный файл, который имеет смысл редактировать - `CodeBattleCpp.cpp`. В этом файле указываются параметры подключения к серверу(URL), а также имеется функция `makeTurn`, внутри которой реализована простейшая игровая логика, которая заставляет вашего персонажа двигаться случайным образом.
### Подключение к серверу
Для подключение из клиента игры к серверу необходимо:
* Зарегистрироваться на игровом сервере через любой браузер(если вы этого еще не сделали)
* Залогиниться на игровой сервер под своим пользователем и скопировать URL страницы. Он будет иметь примерно следующий вид `http://server-address/codenjoy-contest/board/player/j2p3kh7mztqz07f2e1sb?code=2490633588462720265&gameName=loderunner`
* Открыть дял редактирования файл `CodeBattleCpp.cpp`, найти строку `const std::string serverUrl = "<put your URL here>";` и заменить `<put your URL here>` на URL, скопированный на прошлом шаге.
* Сохранить файл и пересобрать проект

Если все сделано правильно, то теперь при старте исполняемого файла клиент успешно подключится к серверу.
### Написание собственной стратегии
Для написания собственной стратегии необходимо в файле `CodeBattleCpp.cpp` найти и модифицировать функцию `LodeRunnerAction makeTurn(const GameBoard& board)`. Исходно она выглядит следующим образом:
```cpp
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
```
Данная стратегия принимает на вход экземпляр класса GameBoard, который представляет собой состояние игрового поля в данный момент. Опираясь на состояние объекта `board` вы должны принять решение о том, какое действие должен выполнить ваш персонаж и вернуть соответствующие значение из перечисления `LodeRunnerAction`.

Данная функция вызывается для каждого нового игрового такта с обновленным состоянием игрового поля.
## Игровое API
### Описание методов класса GameBoard
Данный класс представляет собой состояние игрового поля на данном такте сервера. Игровое поле является квадратом и состоит из элементов `BoardElement`.
  ```
  const BoardPoint& getMyPosition() const;
  ```
  Возвращает вашу текущую позицию на игровом поле
  ```
  bool isGameOver() const;
  ```
  Возвращает `true`, если на данном такте ваш персонаж был убит(на следующем такте он воскреснет в случайном месте на карте)
  ```
  bool hasElementAt(const BoardPoint& point, BoardElement element) const;
  ```
  Возвращает `true`, если на позиции `point` на карте находится объект типа `element`
  ```
  BoardElement getElementAt(const BoardPoint& point) const;
  ```
  Возвращает тип элемента, который находится на позиции `point` на карте
  ```
  void printBoard() const;
  ```
  Выводит символьное представление карты на `stdout`. Для расшифровки обозначений смотри файл `BoardElement.h`
  ```
  std::vector<BoardPoint> findAllElements(BoardElement element) const;
  ```
  Возвращает список позиций всех элементов на карте с типом `element`
  ```
  const std::vector<BoardPoint>& getOtherHeroPositions() const;
  ```
  Возвращает список позиций персонажей всех остальных игроков на карте
  ```
  const std::vector<BoardPoint>& getWallPositions() const;
  ```
  Возвращает список позиций всех стен на карте
  ```
  const std::vector<BoardPoint>& getLadderPositions() const;
  ```
  Возвращает список позиций всех лестниц на карте
  ```
  const std::vector<BoardPoint>& getGoldPositions() const;
  ```
  Возвращает список позиций всех кучек золота на карте
  ```
  const std::vector<BoardPoint>& getPipePositions() const;
  ```
  Возвращает список позиций всех труб на карте
  ```
  const std::vector<BoardPoint>& getEnemyPositions() const;
  ```
  Возвращает список позиций всех вражеских персонажей на карте
  ```
  const std::vector<BoardPoint>& getPortals() const;
  ```
  Возвращает список позиций всех порталов на карте
  ```
  const std::vector<BoardPoint>& getShadowPills() const;
  ```
  Возвращает список позиций всех пилюль на карте
  ```
  bool isNearToElement(const BoardPoint& point, BoardElement element) const;
  ```
  Возвращает `true` если в окрестности одной клетки от позиции `point` есть элемент типа `element`
  ```
  bool hasEnemyAt(const BoardPoint& point) const;
  ```
  Возвращает `true` если в позиции `point` есть вражеский персонаж
  ```
  bool hasOtherHeroAt(const BoardPoint& point) const;
  ```
  Возвращает `true` если в позиции `point` есть персонаж другого игрока
  ```
  bool hasWallAt(const BoardPoint& point) const;
  ```
  Возвращает `true` если в позиции `point` есть стена
  ```
  bool hasLadderAt(const BoardPoint& point) const;
  ```
  Возвращает `true` если в позиции `point` есть лестница
  ```
  bool hasGoldAt(const BoardPoint& point) const;
  ```
  Возвращает `true` если в позиции `point` есть кучка золота
  ```
  bool hasPipeAt(const BoardPoint& point) const;
  ```
  Возвращает `true` если в позиции `point` есть труба
  ```
  bool hasShadowAt(const BoardPoint& point) const;
  ```
  Возвращает `true` если в позиции `point` есть пилюля
  ```
  size_t getBoardSize() const;
  ```
  Возвращает длину игрового поля(игровое поле представляет собой квадрат, поэтому достаточно лишь длины)
### BoardPoint class
Данный класс представляет собой точку на игровом поле. Левый верхний угол имеет координату (0,0).
  ```
  BoardPoint shiftLeft(int delta) const noexcept;
  ```
  Возвращает новый экземпляр класса `BoardPoint`, который представляет собой точку на игровом поле, находящуюся от текущей на `delta` позиций слева
  ```
  BoardPoint shiftLeft() const noexcept;
  ```
  Возвращает новый экземпляр класса `BoardPoint`, который представляет собой точку на игровом поле, находящуюся на одну позицию слева от текущей точки
  ```
  BoardPoint shiftRight(int delta) const noexcept;
  ```
  Возвращает новый экземпляр класса `BoardPoint`, который представляет собой точку на игровом поле, находящуюся от текущей на `delta` позиций справа
  ```
  BoardPoint shiftRight() const noexcept;
  ```
  Возвращает новый экземпляр класса `BoardPoint`, который представляет собой точку на игровом поле, находящуюся на одну позицию справа от текущей точки
  ```
  BoardPoint shiftBottom(int delta) const noexcept;
  ```
  Возвращает новый экземпляр класса `BoardPoint`, который представляет собой точку на игровом поле, находящуюся от текущей на `delta` позиций снизу
  ```
  BoardPoint shiftBottom() const noexcept;
  ```
  Возвращает новый экземпляр класса `BoardPoint`, который представляет собой точку на игровом поле, находящуюся на одну позицию ниже текущей точки
  ```
  BoardPoint shiftTop(int delta) const noexcept;
  ```
  Возвращает новый экземпляр класса `BoardPoint`, который представляет собой точку на игровом поле, находящуюся от текущей на `delta` позиций сверху
  ```
  BoardPoint shiftTop() const noexcept;
  ```
  Возвращает новый экземпляр класса `BoardPoint`, который представляет собой точку на игровом поле, находящуюся на одну позицию выше текущей точки
  ```
  int getX() const noexcept;
  ```
  Возвращает координату X текущей точки
  ```
  int getY() const noexcept;
  ```
  Возвращает координату Y текущей точки
  ```
  bool isOutOfBoard(int size) const noexcept;
  ```
  Возвращает `true`, если текущие координаты выходят за рамки игрового поля, размер которого `size`
  ```
  void print() const noexcept;
  ```
  Выводит на stdout координаты
### LodeRunnerAction enumeration
```cpp
enum class LodeRunnerAction {
	GO_LEFT,      // сделать шаг налево
	GO_RIGHT,     // сделать шаг направо
	GO_UP,        // подняться наверх
	GO_DOWN,      // спустится вниз
	DRILL_RIGHT,  // выкопать яму справа от персонажа
	DRILL_LEFT,   // выкопать яму слева от персонажа
	DRILL,        // выкопать яму перед персонажем
	SUICIDE       // убить своего персонажа(он появится на следующем такте в случайном месте на игровом поле)
};
```

### BoardElement enumeration
```cpp
enum class BoardElement : uint8_t
{
	NONE,                         // Пустое место
	BRICK,                        // Разрушимая стена
	INDESTRUCTIBLE_WALL,          // Неразрушимая стена
	DRILL_PIT,                    // Яма в процессе создания
	YELLOW_GOLD,                  // Желтая кучка золота
	GREEN_GOLD,                   // Зеленая кучка золота
	RED_GOLD,                     // Красная кучка золота
	LADDER,                       // Лестница
	PIPE,                         // Труба
	PIT_FILL_1,                   // Яма, которая зарастет через 1 такта
	PIT_FILL_2,                   // Яма, которая зарастет через 2 такта
	PIT_FILL_3,                   // Яма, которая зарастет через 3 такта
	PIT_FILL_4,                   // Яма, которая зарастет через 4 такта
	PORTAL,                       // Портал
	THE_SHADOW_PILL,              // Пилюля
	HERO_DIE,                     // Ваш персонаж умер
	HERO_DRILL_LEFT,              // Ваш персонаж копает яму слева
	HERO_DRILL_RIGHT,             // Ваш персонаж копает яму справа
	HERO_LADDER,                  // Ваш персонаж находится на лестнице
	HERO_LEFT,                    // Ваш персонаж стоит и смотрит влево
	HERO_RIGHT,                   // Ваш персонаж стоит и смотрит вправо
	HERO_FALL_LEFT,               // Ваш персонаж падает и смотрит влево
	HERO_FALL_RIGHT,              // Ваш персонаж падает и смотрит вправо
	HERO_PIPE_LEFT,               // Ваш персонаж находится на трубе и смотрит влево
	HERO_PIPE_RIGHT,              // Ваш персонаж находится на трубе и смотрит вправо
	HERO_SHADOW_DRILL_LEFT,       // Ваш персонаж в форме тени копает яму слева
	HERO_SHADOW_DRILL_RIGHT,      // Ваш персонаж в форме тени копает яму справа
	HERO_SHADOW_LADDER,           // Ваш персонаж в форме тени находится на лестнице
	HERO_SHADOW_LEFT,             // Ваш персонаж в форме тени смотрит налево
	HERO_SHADOW_RIGHT,            // Ваш персонаж в форме тени смотрит направо
	HERO_SHADOW_FALL_LEFT,        // Ваш персонаж в форме тени падает и смотрит налево
	HERO_SHADOW_FALL_RIGHT,       // Ваш персонаж в форме тени падает и смотрит направо
	HERO_SHADOW_PIPE_LEFT,        // Ваш персонаж в форме тени находится на трубе и смотрит налево
	HERO_SHADOW_PIPE_RIGHT,       // Ваш персонаж в форме тени находится на трубе и смотрит направо
	OTHER_HERO_DIE,               // Другой игрок умер на данном такте
	OTHER_HERO_LEFT,              // Другой игрок смотрит налево
	OTHER_HERO_RIGHT,             // Другой игрок смотрит направо
	OTHER_HERO_LADDER,            // Другой игрок находится на лестнице
	OTHER_HERO_PIPE_LEFT,         // Другой игрок находится на трубе и смотрит налево
	OTHER_HERO_PIPE_RIGHT,        // Другой игрок находится на трубе и смотрит направо
	OTHER_HERO_SHADOW_DIE,        // Другой игрок в форме тени умер на данном такте
	OTHER_HERO_SHADOW_LEFT,       // Другой игрок в форме тени смотрит налево
	OTHER_HERO_SHADOW_RIGHT,      // Другой игрок в форме тени смотрит направо
	OTHER_HERO_SHADOW_LADDER,     // Другой игрок в форме тени находится на лестнице
	OTHER_HERO_SHADOW_PIPE_LEFT,  // Другой игрок в форме тени находится на трубе и смотрит влево
	OTHER_HERO_SHADOW_PIPE_RIGHT, // Другой игрок в форме тени находится на трубе и смотрит вправо
	ENEMY_LADDER,                 // Вражеский персонаж находится на лестнице
	ENEMY_LEFT,                   // Вражеский персонаж смотрит налево
	ENEMY_RIGHT,                  // Вражеский персонаж смотрит направо
	ENEMY_PIPE_LEFT,              // Вражеский персонаж находится на трубе и смотрит налево
	ENEMY_PIPE_RIGHT,             // Вражеский персонаж находится на трубе и смотрит направо
	ENEMY_PIT                     // Вражеский персонаж находится в яме
};
```