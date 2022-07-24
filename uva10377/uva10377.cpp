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

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

#define KEY_RIGHT   'R'
#define KEY_LEFT    'L'
#define KEY_FORWARD 'F'
#define KEY_QUIT    'Q'

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

class Maze {
public:
  explicit Maze(string input);
  ~Maze() = default;

  void InitMap(char event);
  int EventProcess(char event);
  bool isWall(int row, int column);
  void SetPosition();
  std::vector<std::vector<char>> &getMap() { return maze_map_; }
  RobotNode &getRobotNode() { return robot_node_; }
  void showMap();
  void showRobot();

private:
  RobotNode robot_node_;
  vector<vector<char>> maze_map_;
 // std::map<int, string> mapValue;
  int robot_dir_;
};

Maze::Maze(string input) {
    
}

bool Maze::isWall(int row, int column) {
  if (maze_map_[row][column] == '*')
    return true;
  return false; 
}

void Maze::SetPosition() {
    switch (robot_node_.orientation) {
        case NORTH:
            if (!isWall(robot_node_.row-1, robot_node_.column))
                robot_node_.row--;
            break;
        case EAST:
            if (!isWall(robot_node_.row, robot_node_.column-1))
                robot_node_.column++;
            break;
        case SOUTH:
            if (!isWall(robot_node_.row+1, robot_node_.column))
                robot_node_.row++;
            break;
        case WEST:
            if (!isWall(robot_node_.row, robot_node_.column+1))
                robot_node_.column--;
            break;
    }
}

int Maze::EventProcess(char event) {
    int ret = 0;

    switch (event) {
        case KEY_RIGHT: 
            robot_node_.orientation  = (robot_node_.orientation + 1) % 4;
            std::cout << " eventR: " << robot_node_.orientation << std::endl;
            break;
        case KEY_LEFT:  
            robot_node_.orientation  = (robot_node_.orientation + 3) % 4;
            std::cout << " eventL: " << robot_node_.orientation << std::endl;
            break;
        case KEY_FORWARD:    
            std::cout << " eventF: " << robot_node_.orientation << std::endl;
            SetPosition();
            break;
        case KEY_QUIT:  
            std::cout << " eventQ: " << robot_node_.orientation << std::endl;
            ret = 1;
            break;
    }
    return ret;
}

void Maze::showMap() {
    std::cout << "showMap" << std::endl;
    for(auto& row:maze_map_){
        for(auto& col:row){
            std::cout << " "<< col ;
        }
        std::cout << std::endl;
    } 
}

void Maze::showRobot() {
    std::cout << "showRobot" << std::endl;
    std::cout << "Robot Position = " 
      << "(row: "<< robot_node_.row 
      << " ,column: "<< robot_node_.column 
      << ")" << std::endl;
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  int loop;
  bool quit;
  //std::stringstream ss;

  getline(is, input);
  //ss.str(input);
  //ss >> loop;
  loop = stoi(input);
  os << " loop: " << loop << std::endl;
  while (loop--) {
    os << " step1 " << loop << std::endl;
    std::shared_ptr<Maze> maze = std::make_shared<Maze>(input);
    {
        //while (1) {
            os << " step2 " << std::endl;
            getline(is, input);
            os << input << std::endl;

            if(input.empty())
                getline(is, input);
            
            int row, column;
            std::stringstream ss;
            //getline(is, input);
            ss.str(input);
            ss >> row; 
            ss >> column;
            os << " row " << row << std::endl;
            os << " column " << column << std::endl;
        
            std::vector<std::vector<char>> &map = maze->getMap();
            //init map
            while(row--) {
                getline(is, input);
                std::vector<char> v(input.begin(), input.end());
                map.push_back(v);
            }
            maze->showMap();

            RobotNode &robot = maze->getRobotNode();
            getline(is, input);
            std::stringstream ss2;
            ss2.str(input);
            ss2 >> robot.row; 
            ss2 >> robot.column; 
            maze->showRobot();
            
            while(getline(is, input)) {
                //os << " input " << input << std::endl;
                for (const char c : input) {
                    os << " "<< c ;
                    if (maze->EventProcess(c)) {
                        quit = true;
                        os << "quit true..." <<std::endl;
                    }
                    maze->showRobot();
                }
                //os << std::endl;
                if (quit == true) {
                        os << "quit true...break" <<std::endl;
                        break;
                }

            }
            maze->showRobot();
                
               
           
            os << "quit true...break loop " << loop <<std::endl;
            //{
            //}
        //} //while
    }
    //loop --;
    os << " loop--: " << loop << std::endl;
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

#if 0
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
                        "LFF FFRRF R F   F RL LRRLFRLRF F LR LF RFL  FL LRLR FL FL FRLFRRLLRR RFRLLQ\n"
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
                        "FLR  FR LRFFF F R LL  RLFRLFR LR FFRR RR RFRL   LFR F  LLF LFLLRFR  LRLRLRLRF FLRFL  F F FQ\n"
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
