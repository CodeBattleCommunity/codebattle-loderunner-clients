package ru.codebattle.client;

import ru.codebattle.client.api.GameBoard;
import ru.codebattle.client.api.LoderunnerAction;
import ru.codebattle.client.api.LoderunnerBase;

import java.net.URISyntaxException;
import java.util.Random;
import java.util.function.Function;

public class LodeRunnerClient extends LoderunnerBase {

    private Function<GameBoard, LoderunnerAction> callback;
    private final Runnable closeHandler;

    public LodeRunnerClient(String url, Runnable closeHandler) throws URISyntaxException {
        super(url);
        this.closeHandler = closeHandler;
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

    @Override
    public void onClose(int code, String reason, boolean remote) {
        super.onClose(code, reason, remote);
        closeHandler.run();
    }

    public void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    public void initiateExit() {
        setShouldExit(true);
    }
}
