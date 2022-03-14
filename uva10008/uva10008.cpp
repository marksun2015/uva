#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <cctype>

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

using namespace std;

void check_str(string &input_str) {

}

void resolve_uva10008(string &input_str) { 
 std::map<char, int> strmap;
  vector<char> v_alphabets;
  sort(input_str.begin(), input_str.end(), less<int>());

  for(std::string::iterator it = input_str.begin(); it != input_str.end(); ++it) {
    if (isalpha(*it)) 
        v_alphabets.push_back(*it);
  }

  for(std::vector<char>::iterator it = v_alphabets.begin(); it != v_alphabets.end(); ++it) {
      //cout << *it;
      auto item = strmap.find(toupper(*it));
      if (item != strmap.end())
        item->second++; 
      else
        strmap.insert({toupper(*it), 1}); 
  }

  vector<pair<char, int>> vec {strmap.begin(), strmap.end()};

  sort(vec.begin(), vec.end(), 
          [] (auto x, auto y) {return x.second > y.second;});

  //for(map<char, int>::iterator it = strmap.begin(); it != strmap.end(); ++it) {
  //      std::cout << "f:" << it->first <<"  " <<"s:" << it->second << std::endl;
  //} 

  for(vector<pair<char, int>>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << it->first <<" " << it->second << std::endl;
  } 

  return;
}

int main(int argc, char **argv) {
#ifdef ONLINE_JUDGE
#if 1
    int line;
    int i = 0;
    string input;
    string buf_str;

    cin >>line;

    for (i=0; i<=line; i++) {
        getline(cin, input);
        buf_str = buf_str.append(input);
    }
#endif
        
    resolve_uva10008(buf_str);
#else
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}

#ifndef ONLINE_JUDGE
TEST(mapping_str_order_to_int, acending_125634) {
    std::string input_str = std::to_string(125634);
    EXPECT_EQ (mapping_str_order_to_int(input_str, ASCENDING), 123456);
}

TEST(mapping_str_order_to_int, descending_125634) {
    std::string input_str = std::to_string(125634);
    EXPECT_EQ (mapping_str_order_to_int(input_str, DESCENDING), 654321);
}
#endif
