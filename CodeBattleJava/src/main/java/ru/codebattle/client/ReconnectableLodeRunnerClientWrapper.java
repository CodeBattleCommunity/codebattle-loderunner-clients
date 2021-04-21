package ru.codebattle.client;

import lombok.extern.slf4j.Slf4j;
import ru.codebattle.client.api.GameBoard;
import ru.codebattle.client.api.LoderunnerAction;

import java.net.URISyntaxException;
import java.util.function.Function;

@Slf4j
public class ReconnectableLodeRunnerClientWrapper implements Runnable {

    private final String url;
    private final Function<GameBoard, LoderunnerAction> callback;
    private volatile LodeRunnerClient client;

    public ReconnectableLodeRunnerClientWrapper(String url, Function<GameBoard, LoderunnerAction> callback) {
        this.url = url;
        this.callback = callback;
    }

    public synchronized void run() {
        if (client != null) {
            if (client.isShouldExit()) {
                return;
            }
        }
        try {
            client = new LodeRunnerClient(url, this);
            client.run(callback);
        } catch (URISyntaxException e) {
            log.error("Client error.", e);
        }
    }

    public synchronized void initiateExit() {
        if (client != null) {
            client.initiateExit();
        }
    }
}
