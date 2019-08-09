package ru.codebattle.client;

import ru.codebattle.client.api.GameBoard;
import ru.codebattle.client.api.LoderunnerAction;
import ru.codebattle.client.api.LoderunnerBase;

import java.io.Console;
import java.net.URISyntaxException;
import java.util.Random;

public class MyAI extends LoderunnerBase {

    public MyAI(String serverAddress, String user, String code) throws URISyntaxException {
        super(serverAddress, user, code);
        connect();
    }

    @Override
    protected String doMove(GameBoard gameBoard) {
        clearScreen();
        gameBoard.printBoard();
        Random random = new Random(System.currentTimeMillis());
        LoderunnerAction action = LoderunnerAction.values()[random.nextInt(3)];
        System.out.println(action.toString());
        return loderunnerActionToString(action);
    }

    public void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    public void initiateExit()
    {
        setShouldExit(true);
    }
}
