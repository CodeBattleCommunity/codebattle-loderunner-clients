## Требования 

- обязательно наличие .NET Core 3.1;
- среда разработки - MS VisualStudio 2019 или другая, на Ваш выбор.

## Установка для Windows

Скачать и установить MS Visual Studio 2019. Достаточно версии [Community Edition](https://visualstudio.microsoft.com/ru/vs/community/).

## Установка для UNIX
Установка dotnet и .NET Core 3.1 фреймворка осуществляется в соответствии с [рекомендациями от Microsoft](https://docs.microsoft.com/en-us/dotnet/core/install/linux).

Для [установки на ОС Debian 10](https://docs.microsoft.com/en-us/dotnet/core/install/linux-debian) необходимо выполнить следующие шаги:
1. Добавить репозиторий пакетов от Microsoft
```bash
    # добавление репозитория пакетов от Microsoft

    wget https://packages.microsoft.com/config/debian/10/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
    sudo dpkg -i packages-microsoft-prod.deb
```
2. Установить .NET SDK необходимой (3.1) версии 

```bash
    sudo apt-get update; \
      sudo apt-get install -y apt-transport-https && \
      sudo apt-get update && \
      sudo apt-get install -y dotnet-sdk-3.1
```
## Сборка и запуск клиента

### Windows

Для сборки и запуска проекта используйте среду MS Visual Studio.

### Unix
1. Перейти в каталог 'codebattle-loderunner-clients\CodeBattleNet'
2. Выполнить команду для сборки решения:

```bash
    # сборка решения
    dotnet build ./Loderunner.sln
```
3. Запуск клиента осуществляется командой:
```bash
    # запуск клиента
    dotnet run --project ./Loderunner/Loderunner.csproj
```

### Mac (macOS 10.13 "High Sierra" и выше)
1. Установить Command line tools Mac OS

```bash
    xcode-select --install
```
2. Скачать и установить [SDK версии 3.1](https://dotnet.microsoft.com/download/dotnet/3.1) для macOS [Дополнительная информация по установке](https://docs.microsoft.com/ru-ru/dotnet/core/install/macos)

3. Выполнить команду для сборки решения:

```bash
    # сборка решения
    dotnet build ./Loderunner.sln
```
3. Запуск клиента осуществляется командой:
```bash
    # запуск клиента
    dotnet run --project ./Loderunner/Loderunner.csproj
```

## Подключение к серверу игры

Сервер игры Load Runner (https://github.com/codenjoyme/codenjoy) работает по протоколу WebSocket.

Для подключения к игре Вам необходимо получить адрес (ссылку) Вашей игровой комнаты (борды), которая будет выглядеть примерно так: 

http://some-server-address/codenjoy-contest/board/player/u1apyj3djrfgguunpxw0?code=2679320441167088196&gameName=loderunner 

где http://some-server-address - это адрес сервера, и далее url, содержащий id Вашего игрока и начатой игры.

В клиенте в файле **Program.cs** (CodeBattleNet/Loderunner/Program.cs) Вы увидите константное поле **ServerAddress** класса **Program**. В нем необходимо поменять url игры на Ваш собственный: 

```csharp
    class Program
    {
        const string ServerAddress = "http://some-server-address/codenjoy-contest/board/player/jxt3idzs6w9qc1f0tesr?code=3866554102209272582&gameName=loderunner";
        
        ...
    }
```

После этого Вы можете начинать игру.

Пример ответа от сервера игры, который приходит после соединения:

```
☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼
☼ (       (        ( ( (     (~~~~~~~~~  ( (      ~~~~~~~☼
☼##H########################H#H   $   H##########H(      ☼
☼ (H                      $ H######H  H  (    $  H#☼☼☼☼☼#☼
☼H☼☼#☼☼H    H#########H     H#     H#####H#####H##((~~~~~☼
☼H     H    H         H#####H#  ( (H ~   H $   H  ЄЄ((  (☼
☼H#☼#☼#H    H         H  ~~~ #####H#     H $   H    ЄЄ(((☼
☼H  ~  H~~~~H~~~~~~   H           H   H######H##      ЄЄ(☼
☼H     H    H     H###☼☼☼☼☼☼H☼    H~~~H      H   (      #☼
☼H(    H    H#####H     (   H     H      H#########H     ☼
☼☼###☼##☼##☼H         H###H##    H##     H#       ##◄   (☼
☼☼###☼~~~~  H         H   H######H######### H###H #####H#☼
☼☼(((☼      H   ~~~~~~H   H  ( ( H          H# #H   $  H$☼
☼########H###☼☼☼☼     H  ############   ###### ##########☼
☼(       H  (   $  (( H                       ((   ( (   ☼
☼H##########################H########~~~####H############☼
☼H   (     $       ~~~    $ H               H            ☼
☼#######H#######            H###~~~~      ############H  ☼
☼       H~~~~~~~~~~         H                         H  ☼
☼       H    ##H   #######H##########~~~~~~ЄH######## H  ☼
☼    (  H    ##H(      (  H                 H         H  ☼
☼##H#####    ########H#######~~~~  ~~~#########~~~~~  H  ☼
☼  H  (   (          H$                    (      ~~~~H  ☼
☼#########H##########H        #☼☼☼☼☼☼#   ☼☼☼☼☼☼☼      H (☼
☼((       H          H        ~((((( ~                H (☼
☼☼☼       H~~Є~~~~~Є~H (       ######   ###########   H (☼
☼    H######    $    #######H   (       ~~~~~~~~~~~Є~ЄH (☼
☼H☼ (H              ((      H  H####H                 H (☼
☼H☼☼#☼☼☼☼☼☼☼☼☼☼☼☼###☼☼☼☼☼☼☼☼H☼☼☼☼☼☼☼☼#☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼#☼
☼H        «   ~~H~~~~☼☼☼☼☼☼☼H☼☼☼☼☼☼☼      (Q   ~~~~~~~~~H☼
☼H~~ЄЄ  ######  H      (( H☼H☼H        ####H  ☼((   (   H☼
☼Q              ##H#######H☼H☼H######H   ( ###☼☼☼☼☼☼☼☼(~H☼
☼H#########       H    ~~~H☼H☼H~~~   H~~ЄЄ~ ##((( ((  Є H☼
☼H        ###H####H##H(    ☼H☼    (  H  ( (###☼☼☼☼☼☼ ~  H☼
☼H           H      #######☼H☼#####  H#####   ~~~~~~~$~ H☼
☼~~~~~~~~~~~~H       H~~~~~☼H☼~~~~~  H             ~ ~  H☼
☼ (   H            » H ((((☼H☼     ##########H          H☼
☼ ### #############H H#####☼H☼  ( (  $      $H ######## H☼
☼H                 H       ☼H☼#######        H    ((    H☼
☼H#####         H##H####                ###H#########   H☼
☼H      H######### H   ############        H     $( ((( H☼
☼H##    H$         HЄ~~~~~                 H #######H## H☼
☼~~~Є#####H#   ~~~ЄH         ########H     H        H   H☼
☼         H        H      ~~~~~~~~   H     H        H   Q☼
☼   ########H    ######H##        ##############    H   H☼
☼           H    (     H $      ~Є~~~           ##H#####H☼
☼H( ( ###########H     H#####H         H##H       H     H☼
☼H###            H     H     ###########  ##H###  H     H☼
☼H  ######  ##H######  H                    H   ##H###  H☼
☼H(       (  (H ~~~~~##H###H     #########H##           H☼
☼ (  H########H#       H$  ######   (((   H$            H☼
☼ ###H        H         ~~~~~H      ##H###H####H###     H☼
☼    H########H#########     H        H        H        H☼
☼H   H                       H ((     H (      H        H☼
☼H  ####H######((  (    #####H########H##      H#####   H☼
☼H(     H      H#######H                       H       (H☼
☼##############H       H#################################☼
☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼
```

## Написание бота
Логику и то, какие команды отправлять, необходимо прописывать в классе **MyLoderunnerBot**, в методе **DoMove**, которые описаны в файле **MyLoderunnerBot.cs**:

```csharp
    /// <summary>
    /// Called each game tick to make decision what to do (next move)
    /// </summary>
    protected override string DoMove(GameBoard gameBoard)
    {
        //Just print current state (gameBoard) to console
        Console.Clear();
        gameBoard.PrintBoard();


        //TODO: Implement your logic here
        Random random = new Random(Environment.TickCount);
        LoderunnerAction action = (LoderunnerAction)random.Next(3);


        Console.WriteLine(action.ToString());
        return LoderunnerActionToString(action);
    }
```

Вместо:

```csharp
Random random = new Random(Environment.TickCount);
LoderunnerAction action = (LoderunnerAction)random.Next(3);
```

Вы должны указать, какую команду отправить на сервер в качестве Вашего хода.

Полное описание механики игры и список команд можно найти в UI на сервере игры. А так же здесь: https://github.com/Insomnium/codenjoy/blob/master/CodingDojo/games/loderunner/src/main/webapp/resources/help/loderunner.html (та же самая информация, что в UI сервера)

LoderunnerAction (команды которые вы можете отправлять) в клиенте доступны в файле LoderunnerAction.cs в проекте Loderunner.Api:

```csharp
    public enum LoderunnerAction
    {
        GoLeft,
        GoRight,
        GoUp,
        GoDown,
        DrillRight,
        DrillLeft,
        DoNothing,
        Suicide
    }
```

Основной класс для получения информации об игровом поле - это GameBoard (Loderunner.Api). 

## Список методов API (GameBoard) для работы с координатами

**FindAll** - Возвращает список координат для данного типа элемента.

**GetAt** - Возвращает объект элемента в координатах x,y.

**HasElementAt** - Возвращает True, если элемент находится в координатах x, y.

**IsBarrierAt** - Возвращает true, если барьер находится в точке x, y.

**GetMyPosition** - Возвращает точку, в которой находится Ваш герой.

**IsHeroDead** - Возвращает False, если Ваш герой еще жив.

**GetEnemyPositions** - Возвращает список координат для других героев.

**GetOtherHeroPositions** - Возвращает список координат для других героев.

**GetShadowPills** - Возвращает список точек для элементов с типом 'THE_SHADOW_PILL'

**GetPortals** - Возвращает список точек для элементов с типом 'PORTAL'

**GetWallPositions** - Возвращает список точек элементов стен

**GetLadderPositions** - Возвращает набор точек с лестницами

**GetGoldPositions** - Возвращает список точек для элементов с типами YELLOW_GOLD, GREEN_GOLD, RED_GOLD

**GetPipePositions** - Возвращает набор точек pipe

**GetBarriers** - Возвращает список точек барьеров


### Список методов API (GameBoard) для работы с элементами комнаты

**IsNearToElement** - Проверить, существует ли рядом элемент выбранного типа

**HasEnemyAt** - возвращает True, если враг существует в текущей точке

**HasOtherHeroAt** - возвращает True, если другой герой существует в текущей точке

**HasWallAt** - возвращает True, если стена существует в текущей точке

**HasLadderAt** - возвращает True, если лестница существует в текущей точке

**HasGoldAt** - возвращает True, если золото существует в текущей точке

**HasPipeAt** - возвращает True, если pipe существует в текущей точке

**HasShadowAt** - возвращает True, если тень существует в текущей точке

**GetCountElementsNearToPoint** - подсчитывает количество появлений элемента поблизости


### Список доступных Действий (LoderunnerAction)

**GoLeft = "left"** - передвижение игрока влево

**GoRight = "right"** - передвижение игрока вправо

**GoUp = "up"** - передвижение игрока вверх по лестнице

**GoDown = "down"** - передвижение игрока вниз

**DrillRight = "act,right"** - просверлить отверстие вправо

**DrillLeft = "act,left"** - просверлить отверстие влево /
**Если игрок будет использовать только одну команду ACT то отверстие просверлится в направлении, куда смотрит герой.** 

**DoNothing = "stop"** - остановиться

**Suicide = "act(0)"** - завершить игру
