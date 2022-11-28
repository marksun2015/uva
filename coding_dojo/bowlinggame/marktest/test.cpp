#include <vector>
#include <gmock/gmock.h>
#include "Game.hpp"

#if 1
class GameTest: public ::testing::Test
{
public:
    Game game;
    int hit_one();
private:
};

int GameTest::hit_one()
{
    return game.score();
}

TEST_F(GameTest, test)
{
	ASSERT_EQ(1, hit_one());
}
#endif

TEST(Game_Test, test_one)
{
    Game game;
	ASSERT_EQ(1, game.score());
}


