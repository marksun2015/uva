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

enum Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
};

#if 1
class Maze {
public:
  explicit Maze(string input);
  ~Maze() = default;

  void InitMap(char event);
  void EventProcess(char event);

private:
  RobotNode Robot_node_;
 // std::vector<int> combination_;
 // std::map<int, string> mapValue;
  int robot_dir_;
};

Maze::Maze(string input) {
    
}

Maze::EventProcess(char event) {
    switch (event) {
        case Key_Right: 
            Robot_node_.orientation  = (Robot_node_.orientation + 1) % 4;
            //SetPosition(3, 0);  break;
        case Key_Left:  
            Robot_node_.orientation  = (Robot_node_.orientation + 3) % 4;
            //SetPosition(3, 0); break;
        case Key_Forward:    
            SetPosition(0, -3);
        //case Key_Quit:  
            //SetPosition(0, 3);  break;
    }

}
#endif

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  int loop;
  char quit;

  getline(is, input);
  loop = stoi(input);
  os << " loop: " << loop << std::endl;
  while (loop--) {
    //os << " step1 " << loop << std::endl;
    std::shared_ptr<Maze> maze = std::make_shared<Maze>(input);
    {
        while (1) {
            //os << " step2 " << std::endl;
            getline(is, input);
            os << input << std::endl;

            if(input.empty())
                continue;

            //os << " step3 " << std::endl;
            for (const char c : input)
            {
                //os << " "<< c ;
                if (c == 'Q')
                {
                    quit = 'Q';
                }
            }
            //os << std::endl;

            if (quit == 'Q')
            {
                break;
            }
            
            //{
            //}
        } //while
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
