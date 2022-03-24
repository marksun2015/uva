/*
uva10954

    Yup!! The problem name reflects your task; just add a set of numbers. But you may feel yourselves
    condescended, to write a C/C++ program just to add a set of numbers. Such a problem will simply
    question your erudition. So, lets add some flavor of ingenuity to it.
    Addition operation requires cost now, and the cost is the summation of those two to be added. So,
    to add 1 and 10, you need a cost of 11. If you want to add 1, 2 and 3. There are several ways
    1 + 2 = 3, cost = 3     1 + 3 = 4, cost = 4     2 + 3 = 5, cost = 5
    3 + 3 = 6, cost = 6     2 + 4 = 6, cost = 6     1 + 5 = 6, cost = 6
    Total = 9               Total = 10              Total = 11
    I hope you have understood already your mission, to add a set of integers so that the cost is minimal.

    Input
    Each test case will start with a positive number, N (2 ≤ N ≤ 5000) followed by N positive integers
    (all are less than 100000). Input is terminated by a case where the value of N is zero. This case should
    not be processed.

    Output
    For each case print the minimum total cost of addition in a single line.

    Sample Input
    3
    1 2 3
    4
    1 2 3 4
    0

    Sample Output
    9
    1

*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

using namespace std;

void solve_uva10954(string &input_str, ostream &os) {
  vector<char> v_alphabets;
  map<char, int> strmap;
  vector<pair<char, int>> vec;

  get_alphabets(input_str, v_alphabets);
  cal_frequency(v_alphabets, strmap);
  sort_strmap(strmap, vec);

  for (auto it = vec.begin(); it != vec.end(); ++it) {
    os << it->first << " " << it->second << endl;
    //cout << it->first << " " << it->second << endl;
  }

  return;
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  string line;
  string input;
  string buf_str;
  int i = 0;

  getline(is, line);
  for (i = 0; i < stoi(line); i++) {
    getline(is, input);
    buf_str = buf_str.append(input);
  }

  solve_uva10954(buf_str, os);
}

int main(int argc, char **argv) {
#ifdef ONLINE_JUDGE
  solve_uva_problem(std::cin, std::cout);
#else
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}

#ifndef ONLINE_JUDGE
TEST(uva10954, test_string1) {
  std::istringstream iss(
      "3\n"
      "This is a test.\n"
      "Count me 1 2 3 4 5.\n"
      "Wow!!!! Is this question easy?\n");
  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("S 7\n"
            "T 6\n"
            "I 5\n"
            "E 4\n"
            "O 3\n"
            "A 2\n"
            "H 2\n"
            "N 2\n"
            "U 2\n"
            "W 2\n"
            "C 1\n"
            "M 1\n"
            "Q 1\n"
            "Y 1\n",
            oss.str());
}
#endif
