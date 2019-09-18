package ru.codebattle.client.api;

import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Getter
public enum BoardElement {
    NONE(' '),

    BRICK('#'),
    PIT_FILL_1('1'),
    PIT_FILL_2('2'),
    PIT_FILL_3('3'),
    PIT_FILL_4('4'),
    UNDESTROYABLE_WALL('☼'),

    DRILL_PIT('*'),

    ENEMY_LADDER('Q'),
    ENEMY_LEFT('«'),
    ENEMY_RIGHT('»'),
    ENEMY_PIPE_LEFT('<'),
    ENEMY_PIPE_RIGHT('>'),
    ENEMY_PIT('X'),

    GOLD('$'),

    HERO_DIE('Ѡ'),
    HERO_DRILL_LEFT('Я'),
    HERO_DRILL_RIGHT('R'),
    HERO_LADDER('Y'),
    HERO_LEFT('◄'),
    HERO_RIGHT('►'),
    HERO_FALL_LEFT(']'),
    HERO_FALL_RIGHT('['),
    HERO_PIPE_LEFT('{'),
    HERO_PIPE_RIGHT('}'),

    HERO_SHADOW_DRILL_LEFT('⊰'),
    HERO_SHADOW_DRILL_RIGHT('⊱'),
    HERO_SHADOW_LADDER('⍬'),
    HERO_SHADOW_LEFT('⊲'),
    HERO_SHADOW_RIGHT('⊳'),
    HERO_SHADOW_FALL_LEFT('⊅'),
    HERO_SHADOW_FALL_RIGHT('⊄'),
    HERO_SHADOW_PIPE_LEFT('⋜'),
    HERO_SHADOW_PIPE_RIGHT('⋝'),

    OTHER_HERO_DIE('Z'),
    OTHER_HERO_LEFT(')'),
    OTHER_HERO_RIGHT('('),
    OTHER_HERO_LADDER('U'),
    OTHER_HERO_PIPE_LEFT('Э'),
    OTHER_HERO_PIPE_RIGHT('Є'),

    OTHER_HERO_SHADOW_DIE('⋈'),
    OTHER_HERO_SHADOW_LEFT('⋊'),
    OTHER_HERO_SHADOW_RIGHT('⋉'),
    OTHER_HERO_SHADOW_LADDER('⋕'),
    OTHER_HERO_SHADOW_PIPE_LEFT('⊣'),
    OTHER_HERO_SHADOW_PIPE_RIGHT('⊢'),

    LADDER('H'),
    PIPE('~'),

    PORTAL('⊛'),

    THE_SHADOW_PILL('S');

    final char symbol;

    @Override
    public String toString() {
        return String.valueOf(symbol);
    }

    public static BoardElement valueOf(char ch) {
        for (BoardElement el : BoardElement.values()) {
            if (el.symbol == ch) {
                return el;
            }
        }
        throw new IllegalArgumentException("No such element for " + ch);
    }
}
