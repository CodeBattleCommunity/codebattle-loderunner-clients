package ru.codebattle.client.api;

import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Getter
public enum BoardElement {
    NONE(' '),                    // Пустое место – по которому может двигаться герой

    BRICK('#'),                   // Cтена в которой можно просверлить дырочку слева или справа от героя
                                  // (в зависимости от того, куда он сейчас смотрит)

    PIT_FILL_1('1'),              // Стена со временем зарастает. Когда процес начинается - мы видим таймер
    PIT_FILL_2('2'),
    PIT_FILL_3('3'),
    PIT_FILL_4('4'),

    UNDESTROYABLE_WALL('☼'),      // Неразрушаемая стена - в ней ничего просверлить не получится

    DRILL_PIT('*'),               // В момент сверления мы видим процесс так

    // Боты-охотники
    ENEMY_LADDER('Q'),
    ENEMY_LEFT('«'),
    ENEMY_RIGHT('»'),
    ENEMY_PIPE_LEFT('<'),
    ENEMY_PIPE_RIGHT('>'),
    ENEMY_PIT('X'),

    YELLOW_GOLD('$'),             // Горстка золота жёлтого цвета
    GREEN_GOLD('&'),              // Зелёная горстка золота
    RED_GOLD('@'),                // Золото красного цвета

    // Твой герой в зависимости от того, чем он сейчас занят отображается следующими символами
    HERO_DIE('Ѡ'),                // Герой переживает процесс умирания
    HERO_DRILL_LEFT('Я'),         // Герой сверлит слева от себя
    HERO_DRILL_RIGHT('R'),        // Герой сверлит справа от себя
    HERO_LADDER('Y'),             // Герой находится на лестнице
    HERO_LEFT('◄'),               // Герой бежит влево
    HERO_RIGHT('►'),              // Герой бежит вправо
    HERO_FALL_LEFT(']'),          // Герой падает, смотря влево
    HERO_FALL_RIGHT('['),         // Герой падает, смотря вправо
    HERO_PIPE_LEFT('{'),          // Герой ползёт по трубе влево
    HERO_PIPE_RIGHT('}'),         // Герой ползёт по трубе вправо

    // Тоже твой герой, но под таблеткой тени:
    HERO_SHADOW_DIE('x'),         // Герой-тень переживает процесс умирания
    HERO_SHADOW_DRILL_LEFT('⊰'),  // Герой-тень сверлит слева от себя
    HERO_SHADOW_DRILL_RIGHT('⊱'), // Герой-тень сверлит справа от себя
    HERO_SHADOW_LADDER('⍬'),      // Герой-тень находится на лестнице
    HERO_SHADOW_LEFT('⊲'),        // Герой-тень бежит влево
    HERO_SHADOW_RIGHT('⊳'),       // Герой-тень бежит вправо
    HERO_SHADOW_FALL_LEFT('⊅'),   // Герой-тень падает, смотря влево
    HERO_SHADOW_FALL_RIGHT('⊄'),  // Герой-тень падает, смотря вправо
    HERO_SHADOW_PIPE_LEFT('⋜'),   // Герой-тень ползёт по трубе влево
    HERO_SHADOW_PIPE_RIGHT('⋝'),  // Герой-тень ползёт по трубе вправо

    // Герои других игроков отображаются так
    OTHER_HERO_DIE('Z'),          // Герой переживает процесс умирания
    OTHER_HERO_DRILL_LEFT('⌋'),   // Герой сверлит слева от себя
    OTHER_HERO_DRILL_RIGHT('⌊'),  // Герой сверлит справа от себя
    OTHER_HERO_LADDER('U'),       // Герой находится на лестнице
    OTHER_HERO_LEFT(')'),         // Герой бежит влево
    OTHER_HERO_RIGHT('('),        // Герой бежит вправо
    OTHER_HERO_FALL_LEFT('⊐'),    // Герой падает, смотря влево
    OTHER_HERO_FALL_RIGHT('⊏'),   // Герой падает, смотря вправо
    OTHER_HERO_PIPE_LEFT('Э'),    // Герой ползёт по трубе влево
    OTHER_HERO_PIPE_RIGHT('Є'),   // Герой ползёт по трубе вправо

    // А если герои других игроков под таблеткой тени, то так
    OTHER_HERO_SHADOW_DIE('⋈'),         // Другой герой-тень переживает процесс умирания
    OTHER_HERO_SHADOW_DRILL_LEFT('⋰'),  // Другой герой-тень сверлит слева от себя
    OTHER_HERO_SHADOW_DRILL_RIGHT('⋱'), // Другой герой-тень сверлит справа от себя
    OTHER_HERO_SHADOW_LEFT('⋊'),        // Другой герой-тень находится на лестнице
    OTHER_HERO_SHADOW_RIGHT('⋉'),       // Другой герой-тень бежит влево
    OTHER_HERO_SHADOW_LADDER('⋕'),      // Другой герой-тень бежит вправо
    OTHER_HERO_SHADOW_FALL_LEFT('⋣'),   // Другой герой-тень падает, смотря влево
    OTHER_HERO_SHADOW_FALL_RIGHT('⋢'),  // Другой герой-тень падает, смотря вправо
    OTHER_HERO_SHADOW_PIPE_LEFT('⊣'),   // Другой герой-тень ползёт по трубе влево
    OTHER_HERO_SHADOW_PIPE_RIGHT('⊢'),  // Другой герой-тень ползёт по трубе вправо

    LADDER('H'),              // Лестница - по ней можно перемещаться по уровню
    PIPE('~'),                // Труба - по ней так же можно перемещаться по уровню, но только горизонтально

    PORTAL('⊛'),              // Портал - позволяет телепортироваться на карте в иное место на карте

    SHADOW_PILL('S');         // Таблетка тени - наделяют героя дополнительными способностями

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
