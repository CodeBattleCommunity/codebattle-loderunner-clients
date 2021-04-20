import logging

import websocket
from websocket import WebSocketConnectionClosedException
from loderunnerclient.internals.actions import LoderunnerAction
from loderunnerclient.internals.board import Board

logger = logging.getLogger(__name__)

websocket.default_timeout = 3600
class GameClient:
    def __init__(self, url):
        path = url.replace("http", "ws")
        path = path.replace("board/player/", "ws?user=")
        path = path.replace("?code=", "&code=")

        logger.info("connecting... {}".format(path))
        
        self.socket = websocket.WebSocketApp(
            path,
            on_message=lambda ws, msg: self.on_message(ws, msg),
            on_error=lambda ws, err: self.on_error(ws, err),
            on_close=lambda ws: self.on_close(ws),
            on_open=lambda ws: self.on_open(ws),
            on_pong=lambda ws, date: self.on_pong(ws, date)
        )

    def run(self, on_turn=lambda a: LoderunnerAction.DO_NOTHING):
        self.on_turn = on_turn
        while True:
            self.socket.run_forever(ping_interval=60)

    def on_message(self, ws, message):
        board = Board(message.lstrip("board="))
        board.print_board()
        action = self.on_turn(board)
        self.__send(action.value)

    def __send(self, msg):
        logger.info("Sending: {}".format(msg))
        self.socket.send(msg)

    def on_open(self, ws):
        logger.info("Connection established: {}".format(ws))

    def on_error(self, ws, error):
        logger.error(error)
        # to get possible exit on KeyboardInterrupt
        if not isinstance(error, WebSocketConnectionClosedException):
            exit(1)

    def on_close(self, ws):
        logger.info("### disconnected ###")
    
    def on_pong(self, ws, date):
        logger.info("### Looks like game server ON PAUSE ###")