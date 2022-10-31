#include <string>
#include <vector>
#include <gmock/gmock.h>
#include "BowlingGame.hpp"

int BowlingGame::ball_one(std::vector<int>::iterator &pos)
{
	return *pos;		
}

int BowlingGame::ball_two(std::vector<int>::iterator &pos)
{
	return *(pos+1);		
}

int BowlingGame::ball_three(std::vector<int>::iterator &pos)
{
	return *(pos+2);		
}

bool BowlingGame::is_spare(std::vector<int>::iterator &pos)
{
	if (ball_one(pos) + ball_two(pos) == 10)
		return true;

	return false;		
}

bool BowlingGame::is_strike(std::vector<int>::iterator &pos)
{
	if (ball_one(pos) == 10)
		return true;

	return false;		
}


int BowlingGame::open_frame_score(std::vector<int>::iterator &pos)
{
	return ball_one(pos) + ball_two(pos);
}	

int BowlingGame::strike_score(std::vector<int>::iterator &pos)
{
	return 10 + ball_two(pos) + ball_three(pos);
}			

int BowlingGame::spare_score(std::vector<int>::iterator &pos)
{
	return 10 + ball_three(pos);
}			

void BowlingGame::roll(int pin)
{
	score_per_frame.push_back(pin);
}

int BowlingGame::calculate_score_per_frame(std::vector<int>::iterator &pos)
{
		if (is_strike(pos))
		{
			return strike_score(pos);
		}			
		else if (is_spare(pos))
		{
			return spare_score(pos);
		}			
		else 
		{
			return open_frame_score(pos);
		}
}

void BowlingGame::move_to_next_frame(std::vector<int>::iterator &pos)
{
		if (is_strike(pos))
		{
			pos++;
		}			
		else 
		{
			pos += 2;
		}
}

int BowlingGame::score()
{
	int score = 0;
	std::vector<int>::iterator pos = score_per_frame.begin();

	for (int i=0; i<max_frame; i++)
	{
		score += calculate_score_per_frame(pos);
		move_to_next_frame(pos);
	}
	return score;
}

int main(int argc, char** argv)
{
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
