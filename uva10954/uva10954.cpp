/*
uva10954

    Yup!! The problem name reflects your task; just add a set of numbers. But
    you may feel yourselves condescended, to write a C/C++ program just to add a set
    of numbers. Such a problem will simply question your erudition. So, lets add
    some flavor of ingenuity to it. Addition operation requires cost now, and the
    cost is the summation of those two to be added. So, to add 1 and 10, you need a
    cost of 11. If you want to add 1, 2 and 3. There are several ways
    1 + 2 = 3, cost = 3     1 + 3 = 4, cost = 4     2 + 3 = 5, cost = 5
    3 + 3 = 6, cost = 6     2 + 4 = 6, cost = 6     1 + 5 = 6, cost = 6
    Total = 9               Total = 10              Total = 11
    I hope you have understood already your mission, to add a set of integers
    so that the cost is minimal.

    Input
    Each test case will start with a positive number, N (2 ≤ N ≤ 5000) followed
    by N positive integers (all are less than 100000). Input is terminated by a case
    where the value of N is zero. This case should not be processed.

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
    19

*/

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

unsigned int ReadNumbers(const std::string &s, std::vector<int> &v) {
  std::istringstream is(s);
  int n;
  while (is >> n) {
    v.push_back(n);
  }
  return v.size();
}

void cal_minimal_cost(std::string &input_str, int line_number,
                      std::ostream &os) {
  int value = 0;
  int minvalue1, minvalue2;
  unsigned int len;
  std::vector<int> vec;
  std::vector<int> cost;
  std::vector<int> int_list;

  len = ReadNumbers(input_str, int_list);

  vec.assign(int_list.begin(), int_list.end());
  for (unsigned int i = 0; i < (len - 1); i++) {
    auto min1 = std::min_element(std::begin(vec), std::end(vec));
    minvalue1 = *min1;
    vec.erase(min1);

    auto min2 = std::min_element(std::begin(vec), std::end(vec));
    minvalue2 = *min2;
    vec.erase(min2);

    value = minvalue1 + minvalue2;
    cost.push_back(value);
    vec.push_back(value);
    value = 0;
  }

  value = 0;
  for (auto it = cost.begin(); it != cost.end(); ++it) {
    value += *it;
  }
  std::cout << value << std::endl;
  //os << value << std::endl;
  return;
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string line;
  std::string input;
  int line_number;

  while (1) {
    getline(is, line);
    line_number = stoi(line);
    if (line_number != 0) {
      getline(is, input);
      cal_minimal_cost(input, line_number, os);
    } else {
      break;
    }
  }
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
  std::istringstream iss("3\n"
                         "6 5 4\n"
                         "10\n"
                         "9 5 48 2 4 5 6 3 5 4\n"
                         "10\n"
                         "3 4 5 4 7 2 3 8 4 5\n"
                         "0\n");
  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("24\n"
            "224\n"
            "147\n",
            oss.str());
}

TEST(uva10954, test_string2) {
  std::istringstream iss("8\n"
                         "4 4 6 6 8 8 10 10\n"
                         "8\n"
                         "4 6 6 7 7 8 8 9\n"
                         "8\n"
                         "3 4 6 6 6 8 8 9\n"
                         "8\n"
                         "3 4 5 5 5 5 8 9\n"
                         "2\n"
                         "99999 0\n"
                         "4\n"
                         "99997 49999 49999 49999\n"
                         "4\n"
                         "49999 99998 49999 49999\n"
                         "0\n");
  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("166\n"
            "165\n"
            "148\n"
            "130\n"
            "99999\n"
            "499988\n"
            "499990\n",
            oss.str());
}
#endif
