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
        "http://some-server-address/codenjoy-contest/board/player/jxt3idzs6w9qc1f0tesr?code=3866554102209272582&gameName=loderunner"
    )
    gcb.run(turn)


if __name__ == "__main__":
    main()
