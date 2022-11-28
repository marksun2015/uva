#include <string>
#include <vector>
#include <gmock/gmock.h>
#include "Game.hpp"

int Game::score()
{
	return 1;
}

int main(int argc, char** argv)
{
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
