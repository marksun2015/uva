#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

//#define ONLINE_JUDGE

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

void solve_uva10008(string &input_str, ostream &os) {
  vector<char> v_alphabets;
  map<char, int> strmap;
  vector<pair<char, int>> vec;

  get_alphabets(input_str, v_alphabets);
  cal_frequency(v_alphabets, strmap);
  sort_strmap(strmap, vec);

  for (vector<pair<char, int>>::iterator it = vec.begin(); it != vec.end();
       ++it) {
    os << it->first << " " << it->second << endl;
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

  solve_uva10008(buf_str, os);
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
TEST(uva10008, test_string1) {
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

TEST(uva10008, test_string2) {
  std::istringstream iss(
      "4\nMother: \"How was school today, Patrick?\"\nPatrick: \"It was really "
      "great mum! Today we made explosives!\"\nMother: \"Ooh, they do very "
      "fancy stuff with you these days. And what will you do at school "
      "tomorrow?\"\nPatrick: \"What school?\"\n");
  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("O 21\n"
            "T 17\n"
            "A 16\n"
            "E 12\n"
            "H 12\n"
            "S 10\n"
            "R 10\n"
            "Y 9\n"
            "W 9\n"
            "L 8\n"
            "C 7\n"
            "I 7\n"
            "D 7\n"
            "M 6\n"
            "P 4\n"
            "U 4\n"
            "K 3\n"
            "F 3\n"
            "N 2\n"
            "V 2\n"
            "G 1\n"
            "X 1\n",
            oss.str());
}

#endif
