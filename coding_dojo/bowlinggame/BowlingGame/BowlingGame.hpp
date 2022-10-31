class BowlingGame
{
public:
	BowlingGame(){}; 
	~BowlingGame(){}; 
	void roll(int pin);
	int score();
	bool is_spare(std::vector<int>::iterator &pos);
	bool is_strike(std::vector<int>::iterator &pos);
	int ball_one(std::vector<int>::iterator &pos);
	int ball_two(std::vector<int>::iterator &pos);
	int ball_three(std::vector<int>::iterator &pos);
	int open_frame_score(std::vector<int>::iterator &pos);
	int strike_score(std::vector<int>::iterator &pos);
	int spare_score(std::vector<int>::iterator &pos);
	int calculate_score_per_frame(std::vector<int>::iterator &pos);
	void move_to_next_frame(std::vector<int>::iterator &pos);
private:
	std::vector<int> score_per_frame;
	const int max_frame = 10;
};
