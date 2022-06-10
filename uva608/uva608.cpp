/*
uva608

    Sally Jones has a dozen Voyageur silver dollars. However, only eleven of the coins are true silver
    dollars; one coin is counterfeit even though its color and size make it indistinguishable from the real
    silver dollars. The counterfeit coin has a different weight from the other coins but Sally does not know
    if it is heavier or lighter than the real coins.

        Happily, Sally has a friend who loans her a very accurate balance scale. The friend will permit Sally
    three weighings to find the counterfeit coin. For instance, if Sally weighs two coins against each other
    and the scales balance then she knows these two coins are true. Now if Sally weighs one of the true
    coins against a third coin and the scales do not balance then Sally knows the third coin is counterfeit
    and she can tell whether it is light or heavy depending on whether the balance on which it is placed
    goes up or down, respectively.
        
        By choosing her weighings carefully, Sally is able to ensure that she will find the counterfeit coin
    with exactly three weighings.

    Input
    The first line of input is an integer n (n > 0) specifying the number of cases to follow. Each case
    consists of three lines of input, one for each weighing. Sally has identified each of the coins with the
    letters A–L. Information on a weighing will be given by two strings of letters and then one of the words
    “up”, “down”, or “even”. The first string of letters will represent the coins on the left balance; the
    second string, the coins on the right balance. (Sally will always place the same number of coins on the
    right balance as on the left balance.) The word in the third position will tell whether the right side of
    the balance goes up, down, or remains even.

    Output
    For each case, the output will identify the counterfeit coin by its letter and tell whether it is heavy or
    light. The solution will always be uniquely determined.

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

#if 1
class Coins {
public:
  explicit Coins(std::string input);
  ~Coins() = default;

  void StringProcess(std::string input);
  void Union();
  void DifferentWeightProcess();

private:
  std::vector<char> RemoveAppearInUnion(std::vector<string> input);
  void GetInsection(); 
  void SaveUnion(std::string input);

private:
  int NthSubstr(int n, const string& s, const string& p);

  std::vector<std::pair<string, string>> different_coins_;
  std::vector<string> differ_weight_coins_;
  std::vector<char> union_coins_;
  std::vector<string> even_coins_;
  std::vector<string> up_coins_;
  std::vector<string> down_coins_;
};
#endif

Coins::Coins(std::string input) {}

int Coins::NthSubstr(int n, const string& s, const string& p) {
    string::size_type i = s.find(p);     // Find the first occurrence

    int j;
    for (j = 1; j < n && i != string::npos; ++j)
        i = s.find(p, i+1); // Find the next occurrence

    if (j == n)
        return(i);
    else
        return(-1);
}


void Coins::SaveUnion(std::string input) {
  for(long unsigned int i = 0; i < input.length(); i++){
    auto searchResult = std::find(union_coins_.begin(), union_coins_.end(), input[i]);
    if (searchResult == union_coins_.end()){
        std::cout << "--> " << input[i] << std::endl;
        union_coins_.push_back(input[i]);
    }
  }
}
    
void Coins::Union() {
#if 1
  int pos;
  for(long unsigned int i = 0; i < even_coins_.size(); i++) {
      pos = even_coins_[i].find(' ');
      std::cout << "left " << even_coins_[i].substr(0, pos) << std::endl;
      std::string left = even_coins_[i].substr(0, pos);
      SaveUnion(left);
      even_coins_[i].erase(0, pos+1);
      //std::cout << "input remain " << input << std::endl;

      pos = even_coins_[i].find(' ');
      std::cout << "right " << even_coins_[i].substr(0, pos) << std::endl;
      std::string right = even_coins_[i].substr(0, pos);
      SaveUnion(right);
      even_coins_[i].erase(0, pos+1);

      //if(weight.compare("up") == 0){
      //  Union(left);
      //  Union(right);
      //}else {
      //  different_coins_.push_back({left, right});
      //}
      //std::cout << "weight " << input << std::endl;
  }
#endif

}

std::vector<char> Coins::RemoveAppearInUnion(std::vector<string> input) {
#if 1
  //int pos;
  std::vector<char> exist_letter;

  for(long unsigned int i = 0; i < input.size(); i++) {
    for(long unsigned int j = 0; j < input[i].size(); j++) {
        //std::cout << "  " << input[i] << std::endl; 
        //std::cout << "  " << input[i].at(j) << std::endl; 
        //pos = input[i].find(' ');
        auto searchResult = std::find(union_coins_.begin(), union_coins_.end(), input[i].at(j));
        if (searchResult == union_coins_.end()){
            std::cout << "  ....." << input[i].at(j);
            exist_letter.push_back(input[i].at(j));
        }
        
    }
  }
   return exist_letter;
#endif

#if 0
  for(long unsigned int i = 0; i < different_coins_.size(); i++) {
    for(long unsigned int j = 0; j < different_coins_.at(i).first.size(); j++) {
        std::cout << "first  " << different_coins_.at(i).first[j] << std::endl; 
        auto searchResult = std::find(union_coins_.begin(), union_coins_.end(), different_coins_.at(i).first[j]);
            //std::cout << "  left....." << searchResult;
        if (searchResult == union_coins_.end()){
            left_remain.push_back(different_coins_.at(i).first[j]);
        }
        
    }
    
    for(long unsigned int k = 0; k < different_coins_.at(i).second.size(); k++) {
        //std::cout << "second  " << different_coins_.at(i).second[k] << std::endl; 
        auto searchResult = std::find(union_coins_.begin(), union_coins_.end(), different_coins_.at(i).second[k]);
        if (searchResult == union_coins_.end()){
            right_remain.push_back(different_coins_.at(i).second[k]);
        }
    }
  }
#endif

      
  //for (char const &c: left_remain)
  //      std::cout << c << ' ';

#if 0
  for(long unsigned int i = 0; i < left_remain.size(); i++) {
        std::cout << "left remain  " << left_remain[i];
  }

  for(long unsigned int i = 0; i < right_remain.size(); i++) {
        std::cout << "right remain  " << right_remain[i];
  }
  
        //std::cout << "diff f  " << different_coins_.at(i).first[0] 
      //        << " fsize " << different_coins_.at(i).first.size() 
      //        << " s " << different_coins_.at(i).second 
      //        << std::endl;
#endif

}    
    
 
void Coins::GetInsection() {

   
} 
    
void Coins::DifferentWeightProcess() {
  if (!up_coins_.empty())
    RemoveAppearInUnion(up_coins_);
  GetInsection();

#if 0 
  int pos;
  std::vector<char> left_exist_letter;
  std::vector<char> right_exist_letter;
  std::string weight;
  //for (char const &c: union_coins_)
  //      std::cout << c << ' ';
  //std::cout << " DifferentWeightProcess.....";
 
  for (auto &s: differ_weight_coins_) {
    std::cout << s << std::endl;
    pos = s.find(' ');
    std::cout << "left " << s.substr(0, pos) << std::endl;
    std::string left = s.substr(0, pos);
    s.erase(0, pos+1);
    left_exist_letter = RemoveIntersect(left);
    for (auto &c: left_exist_letter)
        std::cout << c << std::endl;

    pos = s.find(' ');
    std::cout << "right " << s.substr(0, pos) << std::endl;
    std::string right = s.substr(0, pos);
    s.erase(0, pos+1);
    right_exist_letter = RemoveIntersect(right);
    for (auto &c: right_exist_letter)
        std::cout << c << std::endl;
    
    weight = s;
  }

   std::cout << "weight " << weight << std::endl;
#endif
}

void Coins::StringProcess(std::string input) {
  int pos;
  //std::string left;
  //std::string right;

  std::string weight;
  pos = NthSubstr(2, input, " "); 
  weight = input.substr(pos + 1, std::string::npos);
  
      std::cout << "weight " << weight <<std::endl;
    //differ_weight_coins_.push_back(input);
  if(weight.compare("even") == 0) {
    even_coins_.push_back(input);
    return;
  }

  if(weight.compare("up") == 0) {
    up_coins_.push_back(input);
    return;
  }
  
  if(weight.compare("down") == 0) {
    down_coins_.push_back(input);
    return;
  }

#if 0
  pos = input.find(' ');
  //std::cout << "left " << input.substr(0, pos) << std::endl;
  std::string left = input.substr(0, pos);
  input.erase(0, pos+1);
  //std::cout << "input remain " << input << std::endl;

  pos = input.find(' ');
  //std::cout << "right " << input.substr(0, pos) << std::endl;
  std::string right = input.substr(0, pos);
  input.erase(0, pos+1);

  //if(input.compare("even") == 0){
  if(weight.compare("up") == 0){
    Union(left);
    Union(right);
  }else {
    different_coins_.push_back({left, right});
  }
  //std::cout << "weight " << input << std::endl;
#endif

}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  int count;

  getline(is, input);
  count = stoi(input);
  std::cout << "count " << count << std::endl;
  //for (i = 0; i < stoi(input); i++) {
    //os << input;
  //}

  //std::shared_ptr<Coins> coins = std::make_shared<Coins>(input);

  while(count--)
  {
    if (input.empty()) {
        break;
    }

    std::shared_ptr<Coins> coins = std::make_shared<Coins>(input);
    {
        for(int i = 0; i < 3; i++) {
            getline(is, input);
            coins->StringProcess(input);
        }
        coins->Union();
        coins->DifferentWeightProcess();
    }
    
  }



  os << "K is the counterfeit coin and it is light.\n";

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
  EXPECT_EQ(
        "K is the counterfeit coin and it is light.\n",
        oss.str());
}

#if 0
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
