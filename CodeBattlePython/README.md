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

Команда выполняется в активированном ранее виртуальном окружении (virtualenv)

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
    
    py loadrunnerclient

```

### Для *nix

```bash
    
    python3 loadrunnerclient

```

Логику и то какие команды отправлять необходимо прописывать в методе **turn** в том же модуле __main__.py:

```python

    def turn(gcb: Board):
        # send random one of possible commands
        # gcb - это основной класс "игрового поля", который вы используете во время игры - именно его методы описываются ниже в README.md
        action_id = random.randint(0, len(LoderunnerAction) - 1)
        return list(LoderunnerAction)[action_id]

```
Вместо `list(LoderunnerAction)[action_id]` вы должны указать какую команду отправить на сервер в качестве вашего хода.

Полное описание механики игры и список команд можно найти в UI на сервере игры. А так же здесь: https://github.com/Insomnium/codenjoy/blob/master/CodingDojo/games/loderunner/src/main/webapp/resources/help/loderunner.html (та же самая информация, что в UI сервера)

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

_find_all - Returns the list of points for the given element type.

get_at - Return an Element object at coordinates x,y.

has_element_at - Return True if Element is at x,y coordinates.

is_barrier_at - Return true if barrier is at x,y.

get_my_position - Return the point where your hero is.

is_game_over - Returns False if your hero still alive.

get_enemy_positions - Return the list of points for other heroes.

get_other_hero_positions - Return the list of points for other heroes.

get_shadow_pills - Return the list of points for elements with type 'THE_SHADOW_PILL'

get_portals - Return the list of points for elements with type 'PORTAL'

get_wall_positions - Returns the list of walls Element Points.

get_ladder_positions - Returns the set of ladder Points

get_gold_positions - Return the list of points for elements with types YELLOW_GOLD, GREEN_GOLD, RED_GOLD

get_pipe_positions - Returns the set of pipe Points

get_barriers - Return the list of barriers Points.

is_near_to_element - Check if near exists element of chosed type

has_enemy_at - return bool if enemy exists in current point

has_other_hero_at - return bool if other hero exists in current point

has_wall_at - return bool if wall exists in current point

has_ladder_at - return bool if ladder exists in current point

has_gold_at - return bool if golf exists in current point

has_pipe_at - return bool if pipe exists in current point

has_shadow_at - return bool if shadow exists in current point

get_count_elements_near_to_point - Counts the number of occurencies of elem nearby
