package ru.codebattle.client.api;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.Objects;

@AllArgsConstructor
@Data
public class BoardPoint {
    private int x;
    private int y;

    /**
     * Checks is current point on board or out of range.
     *
     * @param boardSize Board size to compare
     */
    public boolean isOutOfBoard(int boardSize) {
        return x >= boardSize || y >= boardSize || x < 0 || y < 0;
    }

    /**
     * Returns new BoardPoint object shifted left to "delta" points
     */
    public BoardPoint shiftLeft(int delta) {
        return new BoardPoint(x - delta, y);
    }

    /**
     * Returns new BoardPoint object shifted left to 1 point
     */
    public BoardPoint shiftLeft() {
        return shiftLeft(1);
    }

    /**
     * Returns new BoardPoint object shifted right to "delta" points
     */
    public BoardPoint shiftRight(int delta) {
        return new BoardPoint(x + delta, y);
    }

    /**
     * Returns new BoardPoint object shifted right to 1 point
     */
    public BoardPoint shiftRight() {
        return shiftRight(1);
    }

    /**
     * Returns new BoardPoint object shifted top "delta" points
     */
    public BoardPoint shiftTop(int delta) {
        return new BoardPoint(x, y - delta);
    }

    /**
     * Returns new BoardPoint object shifted top 1 point
     */
    public BoardPoint shiftTop() {
        return shiftTop(1);
    }

    /**
     * Returns new BoardPoint object shifted bottom "delta" points
     */
    public BoardPoint shiftBottom(int delta) {
        return new BoardPoint(x, y + delta);
    }

    /**
     * Returns new BoardPoint object shifted bottom 1 point
     */
    public BoardPoint shiftBottom() {
        return shiftBottom(1);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        BoardPoint that = (BoardPoint) o;
        return x == that.x &&
                y == that.y;
    }

    public boolean notEquals(Object o) {
        return !equals(o);
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }

    @Override
    public String toString() {
        return String.format("[%s,%s]", x, y);
    }
}
