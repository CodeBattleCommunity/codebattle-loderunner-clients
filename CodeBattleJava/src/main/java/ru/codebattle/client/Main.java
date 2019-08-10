package ru.codebattle.client;

import java.io.IOException;
import java.net.URISyntaxException;
import java.util.Random;
import ru.codebattle.client.api.BoardPoint;
import ru.codebattle.client.api.LoderunnerAction;

public class Main {

    private static final String SERVER_ADDRESS = "epruizhsa0001t2.moscow.epam.com:8888";
    private static final String PLAYER_NAME = "0lo7153glmm061u8hdpt";
    private static final String AUTH_CODE = "5427192905953074174";

    public static void main(String[] args) throws URISyntaxException, IOException {
        LodeRunnerClient client = new LodeRunnerClient(SERVER_ADDRESS, PLAYER_NAME, AUTH_CODE);
        client.run(gameBoard -> {
            Random random = new Random(System.currentTimeMillis());
            return LoderunnerAction.values()[random.nextInt(3)];
        });

        System.in.read();

        client.initiateExit();
    }
}
