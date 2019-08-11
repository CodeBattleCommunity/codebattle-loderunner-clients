from loderunnerclient.LodeRunnerClient import GameClient
import random
import logging

from loderunnerclient.internals.actions import LoderunnerAction
from loderunnerclient.internals.board import Board

logging.basicConfig(format='%(asctime)s %(levelname)s:%(message)s',
                    level=logging.INFO)

def turn(gcb: Board):
    action_id = random.randint(0, len(LoderunnerAction)-1)
    return list(LoderunnerAction)[action_id]

if __name__ == '__main__':
    gcb = GameClient("localhost:8080", "<player-id>", "<code>")
    gcb.run(turn)
