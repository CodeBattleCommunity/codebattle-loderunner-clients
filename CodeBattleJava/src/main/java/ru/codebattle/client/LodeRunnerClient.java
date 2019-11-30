package ru.codebattle.client;

import java.util.function.Consumer;
import java.util.function.Function;
import ru.codebattle.client.api.GameBoard;
import ru.codebattle.client.api.LoderunnerAction;
import ru.codebattle.client.api.LoderunnerBase;

import java.io.Console;
import java.net.URISyntaxException;
import java.util.Random;

public class LodeRunnerClient extends LoderunnerBase {

    private Function<GameBoard, LoderunnerAction> callback;

    public LodeRunnerClient(String url) throws URISyntaxException {
        super(url);
    }

    public void run(Function<GameBoard, LoderunnerAction> callback) {
        connect();
        this.callback = callback;
    }

    @Override
    protected String doMove(GameBoard gameBoard) {
        clearScreen();
        gameBoard.printBoard();
        Random random = new Random(System.currentTimeMillis());
        LoderunnerAction action = callback.apply(gameBoard);
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
