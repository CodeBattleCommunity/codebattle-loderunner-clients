package ru.codebattle.client;

import ru.codebattle.client.api.GameBoard;
import ru.codebattle.client.api.LoderunnerBase;

import java.io.IOException;
import java.net.URISyntaxException;

public class Main {

    private static final String SERVER_ADDRESS = "epruizhsa0001t2.moscow.epam.com:8888";
    private static final String PLAYER_NAME = "0lo7153glmm061u8hdpt";
    private static final String AUTH_CODE = "5427192905953074174";

    public static void main(String[] args) throws URISyntaxException, IOException {
        MyAI myAI = new MyAI(SERVER_ADDRESS, PLAYER_NAME, AUTH_CODE);

        System.in.read();

        myAI.initiateExit();
    }
}
