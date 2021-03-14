#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "GameBoard.h"
#include "BoardPoint.h"

TEST(GameBoardTest, hasElementAtTest) {
    const std::string map(u8"☼☼☼⋝⋝⋝⋊⋊⋊");
    GameBoard board(map.cbegin(), map.cend());

    EXPECT_TRUE(board.hasElementAt({0,0}, BoardElement::INDESTRUCTIBLE_WALL));
    EXPECT_TRUE(board.hasElementAt({1,0}, BoardElement::INDESTRUCTIBLE_WALL));
    EXPECT_TRUE(board.hasElementAt({2,0}, BoardElement::INDESTRUCTIBLE_WALL));

    EXPECT_TRUE(board.hasElementAt({0,1}, BoardElement::HERO_SHADOW_PIPE_RIGHT));
    EXPECT_TRUE(board.hasElementAt({1,1}, BoardElement::HERO_SHADOW_PIPE_RIGHT));
    EXPECT_TRUE(board.hasElementAt({2,1}, BoardElement::HERO_SHADOW_PIPE_RIGHT));

    EXPECT_TRUE(board.hasElementAt({0,2}, BoardElement::OTHER_HERO_SHADOW_LEFT));
    EXPECT_TRUE(board.hasElementAt({1,2}, BoardElement::OTHER_HERO_SHADOW_LEFT));
    EXPECT_TRUE(board.hasElementAt({2,2}, BoardElement::OTHER_HERO_SHADOW_LEFT));
}

TEST(GameBoardTest, getMyPositionTest) {
    const std::string map(u8"☼☼☼⋊⋊⋊⋝⊛⊛");
    GameBoard board(map.cbegin(), map.cend());

    const auto pos = board.getMyPosition();
    EXPECT_EQ(pos.getX(), 0);
    EXPECT_EQ(pos.getY(), 2);
}

TEST(GameBoardTest, getGoldPositionsTest) {
    const std::string map(u8"☼☼☼$&@⋝⊛⊛");
    GameBoard board(map.cbegin(), map.cend());
    const auto positions = board.getGoldPositions();
    std::list<BoardPoint> expected{{0,1}, {1,1}, {2,1}};
    EXPECT_THAT(positions, testing::UnorderedElementsAreArray(expected));
}