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
    19

*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iterator>  // std::begin, std::end

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

using namespace std;

template<typename T>
void printVectorElements(vector<T> &vec)
{
    for (auto i = 0; i < vec.size(); ++i) {
        cout << "(" << vec.at(i).first << ","
            << vec.at(i).second << ")" << "; ";
    }
    cout << endl;
}

bool custom_compare(const pair<int, int> &p1, const pair<int, int> &p2)
{
  return (p1.first < p2.first);
    //((1.second == p2.second) && (p1.first < p2.first));
}

int ReadNumbers(const string &s, vector <int> &v) {
    istringstream is(s);
    int n;
    while( is >> n ) {
        v.push_back(n);
    }
    return v.size();
}

void solve_uva10954(string &input_str, int line_number, ostream &os) {
  int value = 0; 
  string number; 
  int min_cost = 1000000000;
  vector <int> cost;
  vector<int> vec;
  //map <int, int> cal_str;
  //vector<pair<int, int>> vec;
  //sort(input_str.begin(), input_str.end(), less<int>());
  //cout << "len: " << line_number << endl;
  //for (auto it = cal_str.begin(); it!=cal_str.end(); ++it){
  //  it.first
  //}
  std::vector<int> int_list;
  ReadNumbers(input_str, int_list);
   //for (int i = 0; i < int_list.size(); i++ ) {
   //     cout << "number is " <<  int_list[i] << endl;
   //}
   //strtk::parse(input_str," ",int_list);

  //for (auto it = int_list.begin(); it != int_list.end(); ++it) {
  //      vec.push_back(make_pair(*it, 0));
  //}
  //cout << "size: " << int_list.size() << endl;

#if 0
  sort(int_list.begin(), int_list.end());
  do { 
      for (auto it = int_list.begin(); it != int_list.end(); ++it) {
          //cout << result->first << endl;
          //cout << value << "+" << result->first << "="<< value + result->first  << endl;
          value += *it;
          cost.push_back(value);
          //result->second = 1;
          //vec.erase(result);
          //if (it->second == 0)
          //    cout << it->first << endl;
      }

      value = 0;
      for (auto it = cost.begin()+1; it != cost.end(); ++it) {
            //cout << "cost: " << *it << endl;
            value += *it;
      }
      //cout << "value: " << value << endl;
      if (value < min_cost)
          min_cost = value;
      value = 0;
      cost.clear();
  } while (next_permutation(int_list.begin(), int_list.end()));
      cout << ">>>>>>> min cost: " << min_cost << endl;
#endif

  int minvalue1;
  int minvalue2;
#if 1
  vec.assign(int_list.begin(), int_list.end());
  //for (auto it = vec.begin(); it != vec.end(); ++it) {
  //      cout << " "  << *it ;
  //}
  //cout << endl;
  //cout << "vec size: " << vec.size() << endl;
  for (unsigned int i = 0; i < (int_list.size()-1); i++) {
    auto min1 = std::min_element(std::begin(vec), std::end(vec));
    minvalue1 = *min1;
    //if (std::end(vec)!=min1)
    //cout << "min1 " << *min1 <<  endl;
    vec.erase(min1);

    auto min2 = std::min_element(std::begin(vec), std::end(vec));
    minvalue2 = *min2;
    //if (std::end(vec)!=min2)
    //cout << "min2 " << *min2 <<  endl;
    vec.erase(min2);
    value = minvalue1 + minvalue2;
    //cout << "value " << value << endl;
    cost.push_back(value);
    vec.push_back(value);
    value = 0;
        
        //cout << value << "+" << result->first << "="<< value + result->first  << endl;
        //value += result->first;
        //cost.push_back(value);
        
        //if (it->second == 0)
        //    cout << it->first << endl;
    }
#endif

#if 0
  for (auto it = input_str.begin(); it != input_str.end(); ++it) {
    //if(*it != '\0'){
    number = *it;
        //cout << "it: " << stoi(&*it) << endl;
        cout << "it: " << number.c_str() << endl;
        cout << "number: " << atoi(number.c_str()) << endl;
    if(atoi(number.c_str()) != 0) {
        value += atoi(number.c_str());
        cost.push_back(value);
    }
  }
#endif
  value = 0;
  for (auto it = cost.begin(); it != cost.end(); ++it) {
        //cout << "cost: " << *it << endl;
        value += *it;
  }
  cout << value << endl;
  //os << value << endl;

  return;
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  string line;
  string input;
  int line_number;

  while(1)
  {
      getline(is, line);
      line_number = stoi(line);

      if(line_number != 0) {
        getline(is, input);
        //cout << endl;
        solve_uva10954(input, line_number, os);
      }else{
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
