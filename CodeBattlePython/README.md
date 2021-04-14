## Требования 

Обязательно наличие Python 3.6 и выше.

## Установка клиента

### Создание virtualenv

Работа со всеми Python проектами проходит внутри изолированных virtualenv окружений.
Поэтому, прежде чем установить клиент - необходимо создать virtualenv.

В Python 3 для создания virtualenv (виртуального окружения) используется команда "python −m venv" и название директории, в которой будет создано виртуальное окружение.

Для активации окружения его надо запустить - для unix и windows используется разный подход.

## Для UNIX
```bash

    python3 -m venv env

    # aктивация окружения
    source env/bin/activate 

```
Для деактивации окружения нужно выполнить команду 

```bash

    deactivate

```
## Для windows

```bash

    python3 -m venv env
    # aктивация окружения
    env\Scripts\activate.bat

```
Для деактивации окружения нужно запустить файл

```bash

    env\Scripts\deactivate.bat

```

## Установка клиента

1. Перейти к codebattle-loderunner-clients\CodeBattlePython>

2. Команда выполняется в активированном ранее виртуальном окружении (virtualenv)

```bash

    pip install -e .

```
## Запуск клиента и подключение к серверу игры

Сервер игры Load Runner (https://github.com/codenjoyme/codenjoy) работает по протоколу WebSocket.

Для подключения к игре Вам необходимо получить адрес (ссылку) вашей игровой комнаты (борды), котора будет выглядеть примерно так: 

http://some-server-address/codenjoy-contest/board/player/u1apyj3djrfgguunpxw0?code=2679320441167088196&gameName=loderunner 

где http://some-server-address будет путь до сервера и далее url содержащая id вашего игрока и начатой игры

В клиенте в файле **__main__.py** (CodeBattlePython/loderunnerclient/main.py) вы увидите метод **def main()** в котором как раз и необходимо поменять url игры на ваш собственный: 

```python


    def main():
        gcb = GameClient(
            # change this url to your
            "http://some-server-address/codenjoy-contest/board/player/jxt3idzs6w9qc1f0tesr?code=3866554102209272582&gameName=loderunner"
        )
        gcb.run(turn)

```

После этого вы можете начать игру командой

### Для windows

```bash
    
    py loderunnerclient

```

### Для *nix

```bash
    
    python3 loderunnerclient

```

Пример ответа от Сервера игры, который приходит после соединения:

```python

2021-03-17 12:26:05,951 INFO:connecting... ws://codebattle2021.westeurope.cloudapp.azure.com/codenjoy-contest/ws?user=some-user-index&gameName=loderunner
2021-03-17 12:26:06,067 INFO:Connection established: <websocket._app.WebSocketApp object at >
☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼☼
☼ H ~~~~     ~~~~                      ~~~~~     ☼             ☼                 ☼
☼ H     ######  H###H  H  H############     ###H   H#########H   H#########H#####☼
☼#☼☼ #       #  H  ##H H H#                    ☼☼☼☼☼         ☼☼☼☼☼         H     ☼
☼    #       #  H  ####H## ~H###############                               H     ☼
☼ ☼☼###H#### #  H~~~~~~~ ~~ H #            #############H##################H~~~~~☼
☼    # H   # #  H           H # ~~~               ~~~~~~~~~~~~~            H #  H☼
☼#☼☼ # H   # ###H  ####H    H #    H#############H             H###########H #  H☼
☼    # H   #    H      H#######    H            ##H  ##☼☼☼##  H##  $       H #  H☼
☼ #### H   #####H#          # #### H~~~~H###### $##H         H##  #####H   H #  H☼
☼    # H ~~      #        ~~~~~~   H    H     ## ######☼☼☼###### ##    #######  H☼
☼~~  # H   H###H ########H      H##H ## H            ~~~~~~~           #   #    H☼
☼    # H   H#  H         ########       H###########         ###########~~~~~~~~H☼
☼ ~~ # H   H#  H                        H  ~~~~~~~            ~~~~~~~ (#    H    ☼
☼    # H   H###H########################H#H       H##########H        (#    H    ☼
☼~ ~~#######   H      $                 H######H  H          H#☼☼☼☼☼# ##### H ###☼
☼            H☼☼#☼☼H    H#########H     H#     H#####H#####H##( ~~~~~ #     H #$ ☼
☼  ##########H     H    H         H#####H#     H ~   H     H  Є~ (    #H#   H #H ☼
☼  ~~       #H#☼#☼#H    H$        H  ~~~ #####H#     H     H    ~Є    #H##### #H ☼
☼ H  ###H####H  ~  H~~~~H~~~~~~   H           H   H######H##      ~~   H      #H ☼
☼ H  ~~~H~~~#H     H    H     H###☼☼☼☼☼☼H☼    H~~~H      H          ######H## #H ☼
☼ H     H   #H     H    H#####H         H     H $    H#########H   ~~~ #  H    H ☼
☼ H     H   #☼###☼##☼##☼H         H###H##    H##     H#       ##          H H####☼
☼       H   #☼###☼~~~~  H         H   H######H######### H###H #####H####### H~~~ ☼
☼  ~~ ##### #☼(((☼      H   ~~~~~~H   H      H          H# #H      H        H    ☼
☼           #########H###☼☼☼☼     H  ############   ###### ###############~~H  ☼☼☼
☼~   ########        H            H                                         H    ☼

```


## Логику и то какие команды отправлять необходимо прописывать в методе **turn** в том же модуле __main__.py:

```python

    def turn(gcb: Board):
        # send random one of possible commands sample
        # gcb - это основной класс "игрового поля", который вы используете во время игры - именно его методы описываются ниже в README.md
        action_id = random.randint(0, len(LoderunnerAction) - 1)
        return list(LoderunnerAction)[action_id]

```

Вместо `list(LoderunnerAction)[action_id]` вы должны указать какую команду отправить на сервер в качестве вашего хода.

Полное описание механики игры и список команд можно найти в UI на сервере игры. А так же здесь: https://dojorena.io/manuals/46.

Actions (команды которые вы можете отправлять) в клиенте доступны в классе LoderunnerAction в модуле internals.actions.py:

```python

    GO_LEFT = "left"
    GO_RIGHT = "right"
    GO_UP = "up"
    GO_DOWN = "down"
    DRILL_RIGHT = "act,right"
    DRILL_LEFT = "act,left"
    DO_NOTHING = "stop"
    SUICIDE = "act(0)"

```

Основной класс для получения информации об игровом поле - это Board (internals.board). 

### Список методов API для работы с координатами

**_find_all** - Возвращает список координат для данного типа элемента.

**get_at** - Возвращает объект элемента в координатах x, y.

**has_element_at** - Возвращает True, если элемент находится в координатах x, y.

**is_barrier_at** - Возвращает True, если барьер находится в точке x, y.

**get_my_position** - Возвращает точку, в которой находится ваш герой.

**is_game_over** - Возвращает False, если ваш герой еще жив.

**get_enemy_positions** - Возвращает список точек для других героев.

**get_other_hero_positions** - Возвращает список точек для других героев.

**get_shadow_pills** - Возвращает список точек для элементов с типом 'THE_SHADOW_PILL'

**get_portals** - Возвращает список точек для элементов с типом 'PORTAL'

**get_wall_positions** - Возвращает список точек элементов стен.

**get_ladder_positions** - Возвращает набор точек лестницы

**get_gold_positions** - Возвращает список точек для элементов с типами YELLOW_GOLD, GREEN_GOLD, RED_GOLD

**get_pipe_positions** - Возвращает набор точек pipe

**get_barriers** - Возвращает список точек барьеров.


### Список методов API для работы с элементами комнаты

**is_near_to_element** - Проверить, существует ли рядом элемент выбранного типа

**has_enemy_at** - возвращает bool, если враг существует в текущей точке

**has_other_hero_at** - возвращает bool, если другой герой существует в текущей точке

**has_wall_at** - возвращает bool, если стена существует в текущей точке

**has_ladder_at** - возвращает bool, если лестница существует в текущей точке

**has_gold_at** - возвращает bool, если золото существует в текущей точке

**has_pipe_at** - возвращает bool, если pipe существует в текущей точке

**has_shadow_at** - возвращает bool, если тень существует в текущей точке

**get_count_elements_near_to_point** - подсчитывает количество появлений элемента поблизости


### Список доступных Действий

**GO_LEFT = "left"** - передвижение игрока влево

**GO_RIGHT = "right"** - передвижение игрока вправо

**GO_UP = "up"** - передвижение игрока вверх по лестнице

**GO_DOWN = "down"** - передвижение игрока вниз

**DRILL_RIGHT = "act,right"** - просверлить отверстие вправо

**DRILL_LEFT = "act,left"** - просверлить отверстие влево /
**Если игрок будет использовать только одну команду ACT то отверстие просверлится в направлении, куда смотрит герой.** 

**DO_NOTHING = "stop"** - остановиться

**SUICIDE = "act(0)"** - завершить игру
