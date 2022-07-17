/*
uva10377 - Maze Traversal

    A common problem in artificial intelligence is negotiation of a maze. A maze has corridors and walls.
    The robot can proceed along corridors, but cannot go through walls.
    
    Input
    The input begins with a single positive integer on a line by itself indicating the number
    of the cases following, each of them as described below. This line is followed by a blank
    line, and there is also a blank line between two consecutive inputs.
    
      For this problem, you will input the dimensions of a maze, as two integer values on the first line.
    Of the two numbers, the first is the number of rows and the second is the number of columns. Neither
    the number of rows nor columns will exceed 60.
      Following these numbers will be a number of rows, as specified previously. In each row there will be
    a character for each column, with the row terminated by the end of line. Blank spaces are corridors,
    asterisks are walls. There needn’t be any exits from the maze.
      Following the maze, will be an initial row and column specified as two integers on one line. This
    gives the initial position of the robot. Initially the robot will be facing North (toward the first row).
      The remaining input will consist of commands to the robot, with any amount of interspersed white-
    space. The valid commands are:
        R rotate the robot 90 degrees clockwise (to the right)
        L rotate the robot 90 degrees counter-clockwise (to the left)
        F move the robot forward, unless a wall prevents this, in which case do nothing
        Q quit the program, printing out the current robot row, column and orientation
    
    Output
      For each test case, the output must follow the description below. The outputs of two consecutive   
    cases will be separated by a blank line.
      The final row and column must be integers separated by a space. The orientation must be one of
    N, W, S, E and separated from the column by a space.
    
    Sample Input
    1

    7 8
    ********
    * * * **
    * *    *
    * * ** *
    * * *  *
    *   * **
    ********
    2 4
    RRFLFF FFR
    FF
    RFFQ

    Sample Output
    5 6 W
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

//#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

struct RobotNode {
  int row;
  int column;
  int orientation;
};

#if 0
class Maze {
public:
  explicit Maze(string input);
  ~Maze() = default;

  void InitCombPosition(int number);
  void CombMaxValue(int offset, int k, int replace_number);
  std::string GetMaxValue() { return mapValue[max_value_]; }

private:
  std::vector<RobotNode> Robot_node_;
  std::vector<int> combination_;
  std::map<int, string> mapValue;
  int max_value_;
};

Poker::Poker(string input) : max_value_(0) {
}
#endif

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  int loop;

  getline(is, input);
  loop = stoi(input);

  os << " loop: " << loop << std::endl;
  while (loop) {
    while (1) {
        getline(is, input);
        if (input.empty()) {
          break;
        }

        os << input << std::endl;
        //std::shared_ptr<Poker> poker = std::make_shared<Poker>(input);
        //{
        //}
    } //while
    loop --;
  } //while
}

int main(int argc, char **argv) {
#ifdef ONLINE_JUDGE
  solve_uva_problem(std::cin, std::cout);
#else
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
#endif
  return 0;
}

#ifndef ONLINE_JUDGE
TEST(uva10377, test_string1) {
  std::istringstream iss("1\n"
                         "7 8\n"
                         "********\n"
                         "* * * **\n"
                         "* *    *\n"
                         "* * ** *\n"
                         "* * *  *\n"
                         "*   * **\n"
                         "********\n"
                         "2 4\n"
                         "RRFLFF FFR\n"
                         "FF\n"
                         "RFFQ\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("5 6 W\n",oss.str());
}
#endif
