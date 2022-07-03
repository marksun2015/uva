/*
uva246

      A simple solitaire card game called 10-20-30 uses a standard deck of 52 playing cards in which suit is
    irrelevant. The value of a face card (king, queen, jack) is 10. The value of an ace is one. The value of
    each of the other cards is the face value of the card (2, 3, 4, etc.). Cards are dealt from the top of the
    deck. You begin by dealing out seven cards, left to right forming seven piles. After playing a card on
    the rightmost pile, the next pile upon which you play a card is the leftmost pile.
      For each card placed on a pile, check that pile to see if one of the following three card combinations
    totals 10, 20, or 30.
        1. the first two and last one,
        2. the first one and the last two, or
        3. the last three cards.

      If so, pick up the three cards and place them on the bottom of the deck. For this problem, always
    check the pile in the order just described. Collect the cards in the order they appear on the pile and
    put them at the bottom of the deck. Picking up three cards may expose three more cards that can be
    picked up. If so, pick them up. Continue until no more sets of three can be picked up from the pile.
      For example, suppose a pile contains 5 9 7 3 where the 5 is at the first card of the pile, and then a
    6 is played. The first two cards plus the last card (5 + 9 + 6) sum to 20. The new contents of the pile
    after picking up those three cards becomes 7 3. Also, the bottommost card in the deck is now the 6,
    the card above it is the 9, and the one above the 9 is the 5.
    
        first --> 5                     first --> 5                     first --> 7
                  9                               9                      last --> 3
                  7                               7
         last --> 3                               3
                                         last --> 6
            
         original pile               after playing 6                  after picking up
    
    
      If a queen were played instead of the six, 5 + 9 + 10 = 24, and 5 + 3 + 10 = 18, but 7 + 3 + 10
    = 20, so the last three cards would be picked up, leaving the pile as 5 9.
   
                  5                               5                             5
                  9                               9                             9
                  7                               7
                  3                               3
                                                  Q
  
          original pile               after playing queen               after picking up

      If a pile contains only three cards when the three sum to 10, 20, or 30, then the pile ”disappears”
    when the cards are picked up. That is, subsequent play skips over the position that the now-empty
    pile occupied. You win if all the piles disappear. You lose if you are unable to deal a card. It is also
    possible to have a draw if neither of the previous two conditions ever occurs.
      Write a program that will play games of 10-20-30 given initial card decks as input.
      
    Input
      Each input set consists of a sequence of 52 integers separated by spaces and/or ends of line. The
    integers represent card values of the initial deck for that game. The first integer is the top card of the
    deck. Input is terminated by a single zero (0) following the last deck.
    Output
      For each input set, print whether the result of the game is a win, loss, or a draw, and print the number
    of times a card is dealt before the game results can be determined. (A draw occurs as soon as the state
    of the game is repeated.) Use the format shown in the “Sample Output” section.
    
    Sample Input
    2 6 5 10 10 4 10 10 10 4 5 10 4 5 10 9 7 6 1 7 6 9 5 3 10 10 4 10 9 2 1 10 1 10 10 10 3 10 9 8 10 8 7 1 2 8 6 7 3 3 8 2
    4 3 2 10 8 10 6 8 9 5 8 10 5 3 5 4 6 9 9 1 7 6 3 5 10 10 8 10 9 10 10 7 2 6 10 10 4 10 1 3 10 1 1 10 2 2 10 4 10 7 7 10
    10 5 4 3 5 7 10 8 2 3 9 10 8 4 5 1 7 6 7 2 6 9 10 2 3 10 3 4 4 9 10 1 1 10 5 10 10 1 8 10 7 8 10 6 10 10 10 9 6 2 10 10
    0
    
    Sample Output
    Win : 66
    Loss: 82
    Draw: 73
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

using VecInt = std::vector<int>;

enum MaxValue {
  WIN ,
  LOSS,
  DRAW
};

struct compare
{
  std::queue<int> key;
  compare(std::queue<int> &state): key(state) {}
 
  bool operator()(std::queue<int> &i) {
    return (i == key);
  }
};

class Poker {
public:
  explicit Poker(std::string input);
  ~Poker() = default;
  void Deal();
  void Output(std::ostream &os);
  int CheckSum(std::deque<int> &pile);
  void Refresh(std::deque<int> &pile, std::queue<int> &handcard);

private:
  int step_;
  int result_;

private:
  int pile_number_;
  int combination_card_;
  VecInt comb_pos_;
  std::deque<int> pile_[7];
  std::queue<int> handcard_;
  std::vector<std::queue<int>> statecard_;
  std::map<int, string> mapValue;
};

Poker::Poker(std::string input)
 :step_(0),
  pile_number_(7),
  combination_card_(3){
  std::stringstream ss(input);
  int cardnumber;
  
  while (ss >> cardnumber) {
    handcard_.push(cardnumber);
  }

  mapValue = {
    {WIN,   "Win : "},
    {LOSS , "Loss: "},
    {DRAW , "Draw: "}
  };
}

void Poker::Output(std::ostream &os) {
  os << mapValue[result_] << step_ << std::endl;
}

void Poker::Refresh(std::deque<int> &pile, std::queue<int> &handcard) {
    for(int i = 0; i < combination_card_; i++) {
      //std::cout << ">>i " << i << " " << pile[comb_pos_[i]] << std::endl;
      handcard_.push(pile[comb_pos_[i]]);
    }

    auto it = pile.begin();
    for(int i = (combination_card_ - 1); i >= 0; i--) {
      pile.erase((it + comb_pos_[i]));
    }

    comb_pos_.clear();
}

int Poker::CheckSum(std::deque<int> &pile) {
  int length = pile.size();
  if ((pile[0]+pile[1]+pile[length-1]) % 10 == 0) {
    //std::cout << " " << pile[0] << " "<< pile[1] << " "<< pile[length - 1] << std::endl;
    comb_pos_.push_back(0);
    comb_pos_.push_back(1);
    comb_pos_.push_back(length-1);
    return 1;
  } else if ((pile[0]+pile[length-2]+pile[length-1]) % 10 == 0) {
    //std::cout << " " << pile[0] << " " << pile[length -2] << " "<< pile[length - 1] << std::endl;
    comb_pos_.push_back(0);
    comb_pos_.push_back(length-2);
    comb_pos_.push_back(length-1);
    return 1;
  } else if ((pile[length-3]+pile[length-2]+pile[length-1]) % 10 == 0) {
    //std::cout << " " << pile[length-3] << " "<< pile[length -2] << " "<< pile[length - 1] << std::endl;
    comb_pos_.push_back(length-3);
    comb_pos_.push_back(length-2);
    comb_pos_.push_back(length-1);
    return 1;
  }
  return 0;
}

void Poker::Deal() {
  int i,j,k;

  for(i = 0; i < (combination_card_-1); i++) {
    for(j = 0; j < pile_number_; j++) {
      pile_[j].push_back(handcard_.front());
      handcard_.pop();
      step_++;
    }
  }

  //deal
  while(1) {
    for(j = 0; j < pile_number_; j++) {
      if(!pile_[j].empty()) {
        pile_[j].push_back(handcard_.front());
        handcard_.pop();
        step_++;

        ///test  
        //std::cout <<"--pile " << j  << "--"<< std::endl ;
        //for(auto &q: pile_[j]) {
        //    std::cout << " " << q ;
        //}
        //std::cout << std::endl;

        while((int)pile_[j].size() >= combination_card_) {
          if(CheckSum(pile_[j])) {
            Refresh(pile_[j], handcard_);
          } else {
            break;
          }
        }

        /* check Win case */
        if (handcard_.size() == 52) {
          result_ = WIN;
          return;
        }

        /* check Loss case */
        if (handcard_.size() == 0) {
          result_ = LOSS;
          return;
        }

        /* check Draw case */
        std::queue<int> state = handcard_;
        for(k = 0; k < pile_number_; k++) {
          for(auto &q: pile_[k]) {
           state.push(q); 
          }
        }

        if (std::find_if(statecard_.begin(), statecard_.end(), compare(state)) != statecard_.end()) {
          result_ = DRAW;
          return;
        } else {
          statecard_.push_back(state);
        }
      }//pile not empty
    }//for loop 
  }//while
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  int count = 1;

  while (1) {
    getline(is, input);
    count = stoi(input.substr(0, 1));
    //std::cout <<"count " << count <<std::endl;

    if (count == 0) {
      break;
    }

    //std::cout <<"input " << input << std::endl ;
    std::shared_ptr<Poker> poker = std::make_shared<Poker>(input);
    {
      poker->Deal();
      poker->Output(os);
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
TEST(uva246, test_string1) {
  std::istringstream iss(
    "2 6 5 10 10 4 10 10 10 4 5 10 4 5 10 9 7 6 1 7 6 9 5 3 10 10 4 10 9 2 1 10 1 10 10 10 3 10 9 8 10 8 7 1 2 8 6 7 3 3 8 2\n"
    "4 3 2 10 8 10 6 8 9 5 8 10 5 3 5 4 6 9 9 1 7 6 3 5 10 10 8 10 9 10 10 7 2 6 10 10 4 10 1 3 10 1 1 10 2 2 10 4 10 7 7 10\n"
    "10 5 4 3 5 7 10 8 2 3 9 10 8 4 5 1 7 6 7 2 6 9 10 2 3 10 3 4 4 9 10 1 1 10 5 10 10 1 8 10 7 8 10 6 10 10 10 9 6 2 10 10\n"
    "0\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("Win : 66\n"
            "Loss: 82\n"
            "Draw: 73\n",
            oss.str());
}
#endif
