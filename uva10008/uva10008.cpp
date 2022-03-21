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

void sort_strmap(map<char, int> &strmap, vector<pair<char, int>> &vec) {
  vec = {strmap.begin(), strmap.end()};
  sort(vec.begin(), vec.end(),
       [](auto x, auto y) { return x.second > y.second; });
}

void cal_frequency(vector<char> &v_alphabets, map<char, int> &strmap) {
  for (vector<char>::iterator it = v_alphabets.begin(); it != v_alphabets.end();
       ++it) {
    auto item = strmap.find(toupper(*it));
    if (item != strmap.end())
      item->second++;
    else
      strmap.insert({toupper(*it), 1});
  }
}

void get_alphabets(string &input_str, vector<char> &v_alphabets) {
  for (string::iterator it = input_str.begin(); it != input_str.end(); ++it) {
    if (isalpha(*it))
      v_alphabets.push_back(*it);
  }
}

void resolve_uva10008(string &input_str, ostream &os) {
  vector<char> v_alphabets;
  map<char, int> strmap;
  vector<pair<char, int>> vec;

  get_alphabets(input_str, v_alphabets);
  cal_frequency(v_alphabets, strmap);
  sort_strmap(strmap, vec);

  for (vector<pair<char, int>>::iterator it = vec.begin(); it != vec.end();
       ++it) {
    // std::cout << it->first <<" " << it->second << std::endl;
    os << it->first << " " << it->second << endl;
  }

  return;
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  string line;
  int i = 0;
  string input;
  string buf_str;

  getline(is, line);
  for (i = 0; i < stoi(line); i++) {
    getline(is, input);
    buf_str = buf_str.append(input);
  }

  resolve_uva10008(buf_str, os);
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
TEST(uva10008, test_string) {
  std::istringstream iss("3\nThis is a test.\nCount me 1 2 3 4 5.\nWow!!!! Is "
                         "this question easy?\n");
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
