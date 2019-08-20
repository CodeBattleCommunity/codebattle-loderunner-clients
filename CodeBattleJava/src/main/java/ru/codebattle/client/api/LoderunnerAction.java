package ru.codebattle.client.api;

import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Getter
public enum LoderunnerAction {
    GO_LEFT,
    GO_RIGHT,
    GO_UP,
    GO_DOWN,
    DRILL_RIGHT,
    DRILL_LEFT,
    DO_NOTHING,
    SUICIDE
}
