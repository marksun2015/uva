/*
uva514

      There is a famous railway station in PopPush City. Country there is incredibly hilly. The station
    was built in last century. Unfortunately, funds were extremely limited that time. It was possible to
    establish only a surface track. Moreover, it turned out that the station could be only a dead-end one
    (see picture) and due to lack of available space it could have only one track.
                                             
            ----------------_          _-----------------
             5,4,3,2,1       -_      _-        1,2,3,4,5
            --------------_    -_  _-    _---------------
                           -_   _--_   _- 
            <-----           -_-    -_-            <-----
               B               |    |                A
                               |    |
                               |    |
                               |    |
                               |    |
                              
                              station


      The local tradition is that every train arriving from the direction A continues in the direction
    B with coaches reorganized in some way. Assume that the train arriving from the direction A has
    N ≤ 1000 coaches numbered in increasing order 1, 2, . . . , N . The chief for train reorganizations must
    know whether it is possible to marshal coaches continuing in the direction B so that their order will
    be a1.a2, . . . , aN . Help him and write a program that decides whether it is possible to get the required
    order of coaches. You can assume that single coaches can be disconnected from the train before they
    enter the station and that they can move themselves until they are on the track in the direction B. You
    can also suppose that at any time there can be located as many coaches as necessary in the station.
    But once a coach has entered the station it cannot return to the track in the direction A and also once
    it has left the station in the direction B it cannot return back to the station.
    
    Input
      The input file consists of blocks of lines. Each block except the last describes one train and possibly
    more requirements for its reorganization. In the first line of the block there is the integer N described
    above. In each of the next lines of the block there is a permutation of 1, 2, . . . , N . The last line of the
    block contains just ‘0’.
      The last block consists of just one line containing ‘0’.
    
    Output
      The output file contains the lines corresponding to the lines with permutations in the input file. A line
    of the output file contains ‘Yes’ if it is possible to marshal the coaches in the order required on the
    corresponding line of the input file. Otherwise it contains ‘No’. In addition, there is one empty line after
    the lines corresponding to one block of the input file. There is no line in the output file corresponding
    to the last “null” block of the input file.
    
    Sample Input
    5
    1 2 3 4 5
    5 4 1 2 3
    0
    6
    6 5 4 3 2 1
    0
    0
    
    Sample Output
    Yes
    No

    Yes 
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

void check_possible(int number, std::string output, std::ostream &os) {
  std::stack<int> station;
  std::queue<int> train_in;
  std::queue<int> train_out;
  int failed = 0;
  int pos = 0;
  
  for(int i=1; i<=number; i++)
    train_in.push(i);

  for(int i=1; i<=number; i++) {
    pos = output.find(' ');
    //std::cout << " "  << stoi(output.substr(0, pos));
    train_out.push(stoi(output.substr(0, pos)));
    output.erase(0, pos + 1);
  }
  //std::cout << std::endl;

  while(!train_in.empty() || !station.empty()) 
  {
    if ((!train_in.empty()) && (train_out.front() == train_in.front())) {
      train_out.pop();
      train_in.pop();
    } else if ((!station.empty()) && (train_out.front() == station.top())) {
      train_out.pop();
      station.pop();
    } 
    else {
      if(!train_in.empty()){
        station.push(train_in.front());
        train_in.pop();
      } else {
        failed = 1;
        break;
      }
    } 
  } 

  if(failed)
    os << "No" << std::endl; 
  else
    os << "Yes" << std::endl;
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  std::string output;
  int train_number;

  while (1) {
    getline(is, input);

    train_number = stoi(input);

    if (train_number == 0) {
        break;
    }
 
    while (1) {
      getline(is, output);

      if(stoi(output.substr(0, 1)) == 0) {
        break;
      }

      check_possible(train_number, output, os);
    }

    os << std::endl;
  }
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
TEST(uva514, test_string1) {
  std::istringstream iss(
            "10\n"
            "5 7 10 9 8 6 4 3 2 1\n"
            "5 6 4 8 7 3 2 9 1 10\n"
            "0\n"
            "0\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("Yes\n"
            "Yes\n"
            "\n",
            oss.str());
}
#endif
