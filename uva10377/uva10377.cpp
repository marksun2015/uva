/*
uva10377 - Maze Traversal

      A common problem in artificial intelligence is negotiation of a maze. A maze
    has corridors and walls. The robot can proceed along corridors, but cannot go
    through walls.

    Input
      The input begins with a single positive integer on a line by itself
    indicating the number of the cases following, each of them as described below.
    This line is followed by a blank line, and there is also a blank line between
    two consecutive inputs.

      For this problem, you will input the dimensions of a maze, as two integer
    values on the first line. Of the two numbers, the first is the number of rows
    and the second is the number of columns. Neither the number of rows nor columns
    will exceed 60.
      Following these numbers will be a number of rows, as specified previously. In
    each row there will be a character for each column, with the row terminated by
    the end of line. Blank spaces are corridors, asterisks are walls. There needn’t
    be any exits from the maze.
      Following the maze, will be an initial row and column specified as two integers
    on one line. This gives the initial position of the robot. Initially the robot will
    be facing North (toward the first row). The remaining input will consist of commands
    to the robot, with any amount of interspersed white- space. The valid commands are:
        R rotate the robot 90 degrees clockwise (to the right)
        L rotate the robot 90 degrees counter-clockwise (to the left)
        F move the robot forward, unless a wall prevents this, in which case do nothing
        Q quit the program, printing out the current robot row, column and orientation

    Output
      For each test case, the output must follow the description below. The outputs of
    two consecutive cases will be separated by a blank line. The final row and column
    must be integers separated by a space. The orientation must be one of N, W, S, E and
    separated from the column by a space.

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

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

#define KEY_RIGHT 'R'
#define KEY_LEFT 'L'
#define KEY_FORWARD 'F'
#define KEY_QUIT 'Q'
#define WALL '*'

struct RobotNode {
  int row;
  int column;
  int orientation;
};

enum Direction {
  NORTH = 0,
  EAST = 1,
  SOUTH = 2,
  WEST = 3,
};

std::map<int, char> mapValue = {
    {NORTH, 'N'}, {EAST, 'E'}, {SOUTH, 'S'}, {WEST, 'W'}};

class Maze {
public:
  explicit Maze();
  ~Maze() = default;

  bool isWall(int row, int column);
  void setPosition();
  int eventProcess(char event);
  void stepProcess(std::istream &is, std::ostream &os);

  void initMap(std::istream &is, std::ostream &os);
  void initRobot(std::istream &is, std::ostream &os);
  void showMap(std::ostream &os);
  void showRobot(std::ostream &os);

  std::vector<std::vector<char>> &getMap() { return maze_map_; }
  RobotNode &getRobotNode() { return robot_node_; }

private:
  RobotNode robot_node_;
  std::vector<std::vector<char>> maze_map_;
};

Maze::Maze() {
  robot_node_ = {};
  maze_map_.clear();
}

bool Maze::isWall(int row, int column) {
  std::vector<std::vector<char>> &map = getMap();
  RobotNode &robot = getRobotNode();

  if (map[row - 1][column - 1] == WALL)
    return true;

  map[robot.row - 1][robot.column - 1] = ' ';

  return false;
}

void Maze::setPosition() {
  RobotNode &robot = getRobotNode();

  switch (robot.orientation) {
  case NORTH:
    if (!isWall(robot.row - 1, robot.column))
      robot.row--;
    break;
  case EAST:
    if (!isWall(robot.row, robot.column + 1))
      robot.column++;
    break;
  case SOUTH:
    if (!isWall(robot.row + 1, robot.column))
      robot.row++;
    break;
  case WEST:
    if (!isWall(robot.row, robot.column - 1))
      robot.column--;
    break;
  }
}

int Maze::eventProcess(char event) {
  std::vector<std::vector<char>> &map = getMap();
  RobotNode &robot = getRobotNode();
  int ret = 0;

  switch (event) {
  case KEY_RIGHT:
    robot.orientation = (robot.orientation + 1) % 4;
    break;
  case KEY_LEFT:
    robot.orientation = (robot.orientation + 3) % 4;
    break;
  case KEY_FORWARD:
    setPosition();
    break;
  case KEY_QUIT:
    ret = -1;
    break;
  }

  map[robot.row - 1][robot.column - 1] = mapValue[robot.orientation];
  return ret;
}

void Maze::stepProcess(std::istream &is, std::ostream &os) {
  std::string input;

  while (getline(is, input)) {
    for (const char c : input) {
      if (eventProcess(c) == -1) {
        return;
      }
      // showMap(os);
    }
  }
}

void Maze::initMap(std::istream &is, std::ostream &os) {
  std::vector<std::vector<char>> &map = getMap();
  std::string input;
  std::stringstream ss;
  int row;

  getline(is, input);
  if (input.empty())
    getline(is, input);

  ss.str(input);
  ss >> row;

  while (row--) {
    getline(is, input);
    std::vector<char> v(input.begin(), input.end());
    map.push_back(v);
  }
  // showMap(os);
}

void Maze::initRobot(std::istream &is, std::ostream &os) {
  std::vector<std::vector<char>> &map = getMap();
  RobotNode &robot = getRobotNode();
  std::string input;
  std::stringstream ss;

  getline(is, input);
  ss.str(input);
  ss >> robot.row;
  ss >> robot.column;
  robot.orientation = NORTH;

  map[robot.row - 1][robot.column - 1] = mapValue[robot.orientation];
  // showMap(os);
}

void Maze::showMap(std::ostream &os) {
  std::vector<std::vector<char>> &map = getMap();
  os << "==== showMap ====" << std::endl;

  for (auto &row : map) {
    for (auto &col : row) {
      os << " " << col;
    }
    os << std::endl;
  }
}

void Maze::showRobot(std::ostream &os) {
  RobotNode &robot = getRobotNode();

  os << robot.row << " " << robot.column << " " << mapValue[robot.orientation]
     << std::endl;
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  int loop;

  getline(is, input);
  loop = stoi(input);

  while (loop--) {
    std::shared_ptr<Maze> maze = std::make_shared<Maze>();
    {
      maze->initMap(is, os);
      maze->initRobot(is, os);
      maze->stepProcess(is, os);
      maze->showRobot(os);

      if (loop != 0) {
        os << std::endl;
      }
    }
  } // while(loop--)
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
  EXPECT_EQ("5 6 W\n", oss.str());
}

#if 1
TEST(uva10377, test_string2) {
  std::istringstream iss("4\n"
                         "\n"
                         "20 21\n"
                         "*********************\n"
                         "*       * ** *  * * *\n"
                         "* ***  *     *   *  *\n"
                         "**  *   * **  *     *\n"
                         "****    *          **\n"
                         "* **  ***        ****\n"
                         "* *   *        * ** *\n"
                         "**    *       *   * *\n"
                         "*     ** *  ** * *  *\n"
                         "* *      *          *\n"
                         "**** ** *       * ***\n"
                         "***    *    *   *   *\n"
                         "*  *   *   *  *** ***\n"
                         "**    *   *   *   * *\n"
                         "*    *    *         *\n"
                         "*       *    * * *  *\n"
                         "*     *    **    ** *\n"
                         "*           * * * * *\n"
                         "*  *    *  **   *   *\n"
                         "*********************\n"
                         "8 11\n"
                         "LFF FFRRF R F   F RL LRRLFRLRF F LR LF RFL  FL LRLR "
                         "FL FL FRLFRRLLRR RFRLLQ\n"
                         "\n"
                         "15 11\n"
                         "***********\n"
                         "**     *  *\n"
                         "**   *    *\n"
                         "* * * **  *\n"
                         "* *  * *  *\n"
                         "*    *    *\n"
                         "* *   * * *\n"
                         "***   * * *\n"
                         "*   * * * *\n"
                         "** **   * *\n"
                         "*   *     *\n"
                         "*    ** * *\n"
                         "*        **\n"
                         "**   ** * *\n"
                         "***********\n"
                         "5 10\n"
                         "FRF RLL  FLLRRRLRFL FFFQ\n"
                         "\n"
                         "12 14\n"
                         "**************\n"
                         "*     *    ***\n"
                         "* *  *    * **\n"
                         "*            *\n"
                         "****  * **  **\n"
                         "* *  *     * *\n"
                         "*  *         *\n"
                         "* *    *     *\n"
                         "***    *  *  *\n"
                         "*  *   **  ***\n"
                         "* **   *  *  *\n"
                         "**************\n"
                         "11 2\n"
                         "FLR  FR LRFFF F R LL  RLFRLFR LR FFRR RR RFRL   LFR "
                         "F  LLF LFLLRFR  LRLRLRLRF FLRFL  F F FQ\n"
                         "\n"
                         "21 13\n"
                         "*************\n"
                         "** *   *    *\n"
                         "*  *      ***\n"
                         "*        *  *\n"
                         "* * ***     *\n"
                         "*     *  ****\n"
                         "*     *     *\n"
                         "** **    ** *\n"
                         "*     ** ****\n"
                         "*    **  *  *\n"
                         "** *  *   ***\n"
                         "**  *       *\n"
                         "*        *  *\n"
                         "** **       *\n"
                         "**   **     *\n"
                         "*       *   *\n"
                         "*  **   * * *\n"
                         "*      * *  *\n"
                         "* *      ** *\n"
                         "**   * **  **\n"
                         "*************\n"
                         "7 6\n"
                         "LRL   LRRLFRF  FLR RRFFR  RF RR RFF FFL FQ\n");
  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("11 5 E\n"
            "\n"
            "2 10 N\n"
            "\n"
            "11 2 S\n"
            "\n"
            "7 2 S\n",
            oss.str());
}
#endif

#endif
