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

def main():
    gcb = GameClient("http://codebattle-spb-2019.francecentral.cloudapp.azure.com/codenjoy-contest/board/player/jxt3idzs6w9qc1f0tesr?code=3866554102209272582&gameName=loderunner")
    gcb.run(turn)
