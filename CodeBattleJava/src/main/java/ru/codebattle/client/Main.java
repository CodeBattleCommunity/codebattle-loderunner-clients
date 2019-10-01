package ru.codebattle.client;

import java.io.IOException;
import java.net.URISyntaxException;
import java.util.Random;
import ru.codebattle.client.api.BoardPoint;
import ru.codebattle.client.api.LoderunnerAction;

public class Main {

    private static final String SERVER_ADDRESS = "localhost:8080";
    private static final String PLAYER_NAME = "<player-id>";
    private static final String AUTH_CODE = "<code>";

    public static void main(String[] args) throws URISyntaxException, IOException {
        LodeRunnerClient client = new LodeRunnerClient(SERVER_ADDRESS, PLAYER_NAME, AUTH_CODE);
        client.run(gameBoard -> {
            Random random = new Random(System.currentTimeMillis());
            return LoderunnerAction.values()[random.nextInt(LoderunnerAction.values().length)];
        });

        System.in.read();

        client.initiateExit();
    }
}
