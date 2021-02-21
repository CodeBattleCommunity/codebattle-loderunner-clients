import logging
import random

from loderunnerclient.internals.actions import LoderunnerAction
from loderunnerclient.internals.board import Board
from loderunnerclient.game_client import GameClient

logging.basicConfig(format="%(asctime)s %(levelname)s:%(message)s", level=logging.INFO)


def turn(gcb: Board):
    # send random one of possible commands
    action_id = random.randint(0, len(LoderunnerAction) - 1)
    return list(LoderunnerAction)[action_id]


def main():
    gcb = GameClient(
        # change this url to your
        "http://35.228.17.103/codenjoy-contest/board/player/u1apyj3djrfgguunpxw0?code=2679320441167088196&gameName=loderunner"
    )
    gcb.run(turn)


if __name__ == "__main__":
    main()
