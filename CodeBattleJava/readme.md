## Инструкция

### Клиент на java

#### Подготовка 
Чтобы начать работать потребуется **Java 11**. 
Так же Gradle версии 4.8.1 или выше

0. Скопируйте клиент к себе

```bash

    git clone https://github.com/CodeBattleCommunity/codebattle-loderunner-clients.git

```

1. Импортируйте проект как "Gradle project" в вашу IDE Intellij Idea (работа под Eclipse не проверялась)
2. Установите плагин Lombok.

#### Подключение к серверу и начало игры

1. Чтобы подключится к серверу необходимо в файле CodeBattleJava\src\main\java\ru\codebattle\client\Main.java прописать uri сервера игры

```java

public class Main {

    private static final String SERVER_ADDRESS = "http://codingdojo2019.westeurope.cloudapp.azure.com/codenjoy-contest/board/player/kjfserksnckshus?code=3948792673423&gameName=loderunner";


```

2. Метод - **doMove** в LodeRunnerClient.java должен возвращать в качестве ответа действие (String), которое вы хотите сделать.

```java
    protected String doMove(GameBoard gameBoard) {
        clearScreen();
        gameBoard.printBoard();
        Random random = new Random(System.currentTimeMillis());
        LoderunnerAction action = callback.apply(gameBoard);
        System.out.println(action.toString());
        return loderunnerActionToString(action);
    }

```


### Методы API для работы с сервером

Все необходимые методы привязаны к объекту классе GameBoard, который передается как агрумент в главный метод **doMove**


### Список доступных Actions (ход в игре)
Данный тип является обязательным для ответа в методе turn.


GO_LEFT = "left" – передвижение влево;

GO_RIGHT = "right" – передвижение вправо;

GO_UP = "up" - лезть по лестнице вверх;

GO_DOWN = "down" - лезть по лестнице вверх;

DRILL_RIGHT = "act,right" - копать справа;

DRILL_LEFT = "act,left" - копать слева;

DO_NOTHING = "stop" - пропуск хода

SUICIDE = "act(0)" - убийство персонажа (как и при его смерти от врагов будут сняты штрафные очки).

