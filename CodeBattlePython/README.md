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

    python -m venv env

    # aктивация окружения
    source env/bin/activate 

```
Для деактивации окружения нужно выполнить команду 

```bash

    deactivate

```
## Для windows

```bash

    python -m venv env
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
        action_id = random.randint(0, len(LoderunnerAction) - 1)
        return list(LoderunnerAction)[action_id]

```
