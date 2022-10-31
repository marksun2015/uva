#include <vector>
#include <gmock/gmock.h>
#include "BowlingGame.hpp"

class BowlingGameTest: public ::testing::Test
{
public:
    BowlingGame game;
    void roll_one(int pin);
    void roll_spare(int pin1, int pin2);
    void roll_strike();
    void roll_many(int times, int pin);
private:
};

void BowlingGameTest::roll_one(int pin)
{
    game.roll(pin);
}

void BowlingGameTest::roll_spare(int pin1, int pin2)
{
    game.roll(pin1);
    game.roll(pin2);
}

void BowlingGameTest::roll_strike()
{
    game.roll(10);
}

void BowlingGameTest::roll_many(int times, int pin)
{
    for (int i=0; i<times; i++)
        game.roll(pin);
}

TEST(bowling_game_test, test_zero_score)
{
    BowlingGame game;

    for (int i=0; i<20; i++)
        game.roll(0);

	ASSERT_EQ(0, game.score());
}

TEST_F(BowlingGameTest, test_zero_score)
{
    roll_many(20, 0);
	ASSERT_EQ(0, game.score());
}

TEST_F(BowlingGameTest, test_20_score)
{
    roll_many(20, 1);
	ASSERT_EQ(20, game.score());
}

TEST_F(BowlingGameTest, test_spare)
{
    roll_spare(7, 3);
    roll_one(5);
    roll_many(17, 0);
	ASSERT_EQ(20, game.score());
}

TEST_F(BowlingGameTest, test_strike)
{
    roll_strike();
    roll_one(3);
    roll_one(4);
    roll_many(16, 0);
	ASSERT_EQ(24, game.score());
}

TEST_F(BowlingGameTest, test_perfect)
{
    roll_many(12, 10);
	ASSERT_EQ(300, game.score());
}