package ru.codebattle.client;

import java.io.IOException;
import java.net.URISyntaxException;
import java.util.Random;
import ru.codebattle.client.api.BoardPoint;
import ru.codebattle.client.api.LoderunnerAction;

public class Main {

    private static final String SERVER_ADDRESS = "http://codingdojo2019.westeurope.cloudapp.azure.com/codenjoy-contest/board/player/kjfserksnckshus?code=3948792673423&gameName=loderunner";

    public static void main(String[] args) throws URISyntaxException, IOException {
        LodeRunnerClient client = new LodeRunnerClient(SERVER_ADDRESS);
        client.run(gameBoard -> {
            Random random = new Random(System.currentTimeMillis());
            return LoderunnerAction.values()[random.nextInt(LoderunnerAction.values().length)];
        });

        System.in.read();

        client.initiateExit();
    }
}
