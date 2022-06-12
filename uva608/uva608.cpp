/*
uva608

      Sally Jones has a dozen Voyageur silver dollars. However, only eleven of the
    coins are true silver dollars; one coin is counterfeit even though its color and
    size make it indistinguishable from the real silver dollars. The counterfeit
    coin has a different weight from the other coins but Sally does not know if it
    is heavier or lighter than the real coins.

      Happily, Sally has a friend who loans her a very accurate balance scale.
    The friend will permit Sally three weighings to find the counterfeit coin. For
    instance, if Sally weighs two coins against each other and the scales balance
    then she knows these two coins are true. Now if Sally weighs one of the true
      coins against a third coin and the scales do not balance then Sally knows
    the third coin is counterfeit and she can tell whether it is light or heavy
    depending on whether the balance on which it is placed goes up or down,
    respectively.

      By choosing her weighings carefully, Sally is able to ensure that she
    will find the counterfeit coin with exactly three weighings.

    Input
      The first line of input is an integer n (n > 0) specifying the number of
    cases to follow. Each case consists of three lines of input, one for each
    weighing. Sally has identified each of the coins with the letters A–L.
    Information on a weighing will be given by two strings of letters and then one
    of the words “up”, “down”, or “even”. The first string of letters will represent
    the coins on the left balance; the second string, the coins on the right
    balance. (Sally will always place the same number of coins on the right balance
    as on the left balance.) The word in the third position will tell whether the
    right side of the balance goes up, down, or remains even.

    Output
      For each case, the output will identify the counterfeit coin by its letter
    and tell whether it is heavy or light. The solution will always be uniquely
    determined.

    Sample Input
    1
    ABCD EFGH even
    ABCI EFJK up
    ABIJ EFGH even

    Sample Output
    K is the counterfeit coin and it is light.
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

class Coins {
public:
  explicit Coins(std::string input);
  ~Coins() = default;

  void StringProcess(std::string input);
  void SameWeightProcess();
  void DifferentWeightProcess(std::ostream &os);

private:
  int NthSubstr(int n, const string &s, const string &p);
  void RemoveAppearInUnion(std::vector<string> input);
  void InsectionInDifferentWeight(std::vector<string> input_h,
                                  std::vector<string> input_l,
                                  std::ostream &os);

  std::string Union(std::string &v1, std::string &v2);
  std::string Difference(std::string &v1, std::string &v2);
  std::string Intersection(std::string &v1, std::string &v2);

  std::vector<string> different_weight_coins_;
  std::vector<string> same_weight_coins_;

  std::vector<string> heavy_coins_;
  std::vector<string> light_coins_;
  std::string union_conis_;
};

Coins::Coins(std::string input) {}

int Coins::NthSubstr(int n, const string &s, const string &p) {
  string::size_type i = s.find(p); // Find the first occurrence

  int j;
  for (j = 1; j < n && i != string::npos; ++j)
    i = s.find(p, i + 1); // Find the next occurrence

  if (j == n)
    return (i);
  else
    return (-1);
}

std::string Coins::Union(std::string &v1, std::string &v2) {
  std::string v3;
  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
  return v3;
}

std::string Coins::Difference(std::string &v1, std::string &v2) {
  std::string v3;
  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                      back_inserter(v3));
  return v3;
}

std::string Coins::Intersection(std::string &v1, std::string &v2) {
  std::string v3;
  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                        back_inserter(v3));
  return v3;
}

void Coins::RemoveAppearInUnion(std::vector<string> input) {
  std::string string_weight;
  std::string string_difference_removed_union;
  std::string differ_weight_coins;

  for (long unsigned int i = 0; i < input.size(); i++) {
    std::stringstream s(input[i]);
    std::string left;
    std::string right;
    std::string weight;
    std::string string_difference_left;
    std::string string_difference_right;
    s >> left >> right >> weight;

    string_difference_left = Difference(left, union_conis_);
    // std::cout << "==>string_difference_left " << string_difference_left <<
    // std::endl;
    string_difference_right = Difference(right, union_conis_);
    // std::cout << "==>string_difference_right " << string_difference_right <<
    // std::endl;

    if (weight.compare("up") == 0) {
      if (!string_difference_left.empty())
        heavy_coins_.push_back(string_difference_left);
      if (!string_difference_right.empty())
        light_coins_.push_back(string_difference_right);
    }

    if (weight.compare("down") == 0) {
      if (!string_difference_right.empty())
        heavy_coins_.push_back(string_difference_right);
      if (!string_difference_left.empty())
        light_coins_.push_back(string_difference_left);
    }
  }
}

void Coins::InsectionInDifferentWeight(std::vector<string> input_h,
                                       std::vector<string> input_l,
                                       std::ostream &os) {
  std::string intersection_heavy;
  std::string intersection_light;
  std::string temp_intersection;

  // three string intersection
  if (input_h.size() == 3) {
    temp_intersection = Intersection(input_h[0], input_h[1]);
    intersection_heavy = Intersection(temp_intersection, input_h[2]);

    if (!intersection_heavy.empty()) {
      os << intersection_heavy << " is the counterfeit coin and it is heavy.\n";
      return;
    }
  }

  if (input_l.size() == 3) {
    temp_intersection = Intersection(input_l[0], input_l[1]);
    intersection_light = Intersection(temp_intersection, input_l[2]);

    if (!intersection_light.empty()) {
      os << intersection_light << " is the counterfeit coin and it is light.\n";
      return;
    }
  }

  // two string intersection
  if (input_h.size() == 2) {
    intersection_heavy = Intersection(input_h[0], input_h[1]);

    if (!intersection_heavy.empty()) {
      os << intersection_heavy << " is the counterfeit coin and it is heavy.\n";
      return;
    }
  }

  if (input_l.size() == 2) {
    intersection_light = Intersection(input_l[0], input_l[1]);

    if (!intersection_light.empty()) {
      os << intersection_light << " is the counterfeit coin and it is light.\n";
      return;
    }
  }

  // one string
  if (input_h.size() == 1) {
    if (!input_h[0].empty()) {
      os << input_h[0] << " is the counterfeit coin and it is heavy.\n";
      return;
    }
  }

  if (input_l.size() == 1) {
    if (!input_l[0].empty()) {
      os << input_l[0] << " is the counterfeit coin and it is light.\n";
      return;
    }
  }
}

void Coins::DifferentWeightProcess(std::ostream &os) {
  RemoveAppearInUnion(different_weight_coins_);
  InsectionInDifferentWeight(heavy_coins_, light_coins_, os);
}

void Coins::SameWeightProcess() {
  std::string temp_union;
  std::string left;
  std::string right;
  long unsigned int i;

  for (i = 0; i < same_weight_coins_.size(); i++) {
    std::string str_left_right_union;
    std::stringstream s(same_weight_coins_[i]);
    s >> left >> right;
    str_left_right_union = Union(left, right);

    if (i == 1)
      union_conis_ = Union(str_left_right_union, temp_union);
    if (i == 0)
      temp_union = str_left_right_union;
  }

  if (i == 1)
    union_conis_ = temp_union;
}

void Coins::StringProcess(std::string input) {
  int pos;

  std::string weight;
  pos = NthSubstr(2, input, " ");
  weight = input.substr(pos + 1, std::string::npos);

  if (weight.compare("even") == 0) {
    same_weight_coins_.push_back(input);
  } else {
    different_weight_coins_.push_back(input);
  }
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  int count;

  getline(is, input);
  count = stoi(input);
  // std::cout << "count " << count << std::endl;

  while (count--) {
    if (input.empty()) {
      break;
    }

    std::shared_ptr<Coins> coins = std::make_shared<Coins>(input);
    {
      for (int i = 0; i < 3; i++) {
        getline(is, input);
        coins->StringProcess(input);
      }

      coins->SameWeightProcess();
      coins->DifferentWeightProcess(os);
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
  return 0;
}

#ifndef ONLINE_JUDGE
TEST(uva608, test_string1) {
  std::istringstream iss("1\n"
                         "ABCD EFGH even\n"
                         "ABCI EFJK up\n"
                         "ABIJ EFGH even\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("K is the counterfeit coin and it is light.\n", oss.str());
}

#if 1
TEST(uva608, test_string2) {
  std::istringstream iss("15\n"
                         "ABC DEF up\n"
                         "GHI JKL even\n"
                         "EF DA up\n"
                         "AFG JKL down\n"
                         "A J down\n"
                         "A D even\n"
                         "ED FG even\n"
                         "AB CI up\n"
                         "A D up\n"
                         "IL JK even\n"
                         "A B even\n"
                         "E L down\n"
                         "BEF JIL down\n"
                         "J A even\n"
                         "CEF BJI even\n"
                         "AC BD down\n"
                         "AC EF down\n"
                         "A F even\n"
                         "IJK ABC even\n"
                         "C L even\n"
                         "L F up\n"
                         "IJK ABC even\n"
                         "C L even\n"
                         "L F down\n"
                         "ABCDE FGHIJ even\n"
                         "EIL ADJ down\n"
                         "K J even\n"
                         "CBA DEF up\n"
                         "AF BC up\n"
                         "BA CD up\n"
                         "CBA DEF up\n"
                         "A B up\n"
                         "BA CD up\n"
                         "CBA DEF up\n"
                         "B A down\n"
                         "BA CD up\n"
                         "CBA DEF down\n"
                         "AF BC down\n"
                         "BA CD down\n"
                         "CBA DEF down\n"
                         "A B down\n"
                         "BA CD down\n"
                         "CBA DEF down\n"
                         "B A up\n"
                         "BA CD down\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);

  EXPECT_EQ("D is the counterfeit coin and it is light.\n"
            "J is the counterfeit coin and it is heavy.\n"
            "A is the counterfeit coin and it is heavy.\n"
            "E is the counterfeit coin and it is light.\n"
            "L is the counterfeit coin and it is heavy.\n"
            "C is the counterfeit coin and it is light.\n"
            "F is the counterfeit coin and it is light.\n"
            "F is the counterfeit coin and it is heavy.\n"
            "L is the counterfeit coin and it is light.\n"
            "A is the counterfeit coin and it is heavy.\n"
            "A is the counterfeit coin and it is heavy.\n"
            "A is the counterfeit coin and it is heavy.\n"
            "A is the counterfeit coin and it is light.\n"
            "A is the counterfeit coin and it is light.\n"
            "A is the counterfeit coin and it is light.\n",
            oss.str());
}
#endif
#endif
