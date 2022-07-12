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

class Poker {
public:
  explicit Poker(std::string input);
  ~Poker() = default;
  void Deal();
  void Output(std::ostream &os);
  int CheckSum(std::deque<int> &pile);
  void Refresh(std::deque<int> &pile, std::deque<int> &handcard);

private:
  int step_;
  int result_;

private:
  int pile_number_;
  int combination_card_;
  VecInt comb_pos_;
  std::deque<int> pile_[7];
  std::deque<int> handcard_;
  std::vector<std::deque<int>> statecard_;
  std::map<int, string> mapValue;
};

Poker::Poker(std::string input)
 :step_(0),
  pile_number_(7),
  combination_card_(3){
  std::stringstream ss(input);
  int cardnumber;

  for (int i = 0; i < 52; i++) {
    ss >> cardnumber;
    handcard_.push_back(cardnumber);
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

void Poker::Refresh(std::deque<int> &pile, std::deque<int> &handcard) {
    for(int i = 0; i < combination_card_; i++)
      handcard_.push_back(pile[comb_pos_[i]]);

    auto it = pile.begin();
    for(int i = (combination_card_ - 1); i >= 0; i--)
      pile.erase((it + comb_pos_[i]));

    comb_pos_.clear();
}

int Poker::CheckSum(std::deque<int> &pile) {
  int length = pile.size();
  if ((pile[0]+pile[1]+pile[length-1]) % 10 == 0) {
    comb_pos_.push_back(0);
    comb_pos_.push_back(1);
    comb_pos_.push_back(length-1);
    return 1;
  } else if ((pile[0]+pile[length-2]+pile[length-1]) % 10 == 0) {
    comb_pos_.push_back(0);
    comb_pos_.push_back(length-2);
    comb_pos_.push_back(length-1);
    return 1;
  } else if ((pile[length-3]+pile[length-2]+pile[length-1]) % 10 == 0) {
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
      handcard_.pop_front();
      step_++;
    }
  }

  while(1) {
    for(j = 0; j < pile_number_; j++) {
      if(!pile_[j].empty()) {
        pile_[j].push_back(handcard_.front());
        handcard_.pop_front();
        step_++;

        ///test  
        //std::cout <<"--pile " << j  << "--"<< std::endl ;
        //for(auto &q: pile_[j]) { std::cout << " " << q ;}
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

        /* save state */
        std::deque<int> state = handcard_;
        for(k = 0; k < pile_number_; k++) {
          state.insert(state.end(), pile_[k].begin(), pile_[k].end());
        }

        /* check Draw case */
        auto fstate = (std::find(statecard_.begin(), statecard_.end(), state));
        if (fstate != statecard_.end()){
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

    if (count == 0) {
      break;
    }

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

TEST(uva246, test_string2) {
  std::istringstream iss(
    "3 10 3 5 1 2 10 6 9 5 6 3 4 8 9 8 7 10 8 10 1 7 10 10 10 10 2 4 1 4 8 7 10 6 5 5 10 2 10 10 7 4 6 9 10 3 1 10 2 9 10 10\n"
    "3 5 6 4 8 3 10 9 10 4 10 2 10 6 2 10 4 8 6 1 8 10 10 10 1 10 9 10 8 6 3 4 7 10 10 10 9 5 5 7 5 7 1 7 10 2 3 9 10 10 1 2\n"
    "9 4 10 2 3 10 7 10 8 9 10 10 4 10 2 6 8 5 4 9 5 8 10 7 3 2 8 5 10 10 10 1 7 10 6 2 10 6 1 6 1 10 7 5 1 9 10 10 4 10 3 3\n"
    "6 10 2 1 5 10 8 10 7 2 5 4 1 4 3 6 8 1 10 2 5 3 2 7 10 7 5 9 6 8 10 10 10 1 9 10 6 10 4 3 10 3 9 10 4 10 10 7 10 9 10 8\n"
    "6 10 3 10 9 5 4 3 4 5 10 2 5 2 3 10 10 10 10 10 9 7 1 1 2 7 6 9 7 8 10 3 10 4 7 10 2 6 4 10 8 10 8 1 10 8 10 1 9 5 6 10\n"
    "10 5 10 10 10 8 4 10 10 6 10 7 10 6 8 3 10 2 5 2 7 9 3 6 4 8 9 6 1 5 5 2 7 10 10 4 1 8 10 1 10 10 10 2 10 3 3 7 1 9 4 9\n"
    "10 9 6 6 8 8 2 10 3 4 9 1 7 7 2 3 4 7 5 5 9 10 1 6 2 10 5 3 4 9 6 10 10 10 10 3 10 1 10 7 2 4 8 10 1 5 10 10 8 10 10 10\n"
    "9 6 10 10 4 2 10 7 9 7 8 4 10 6 7 4 5 10 1 5 10 5 1 9 10 3 1 10 10 10 10 5 3 10 10 8 10 9 2 4 2 8 3 6 1 2 10 7 3 6 8 10\n"
    "10 2 4 10 10 10 8 10 10 1 3 5 10 10 5 6 9 10 4 10 8 3 7 10 9 10 9 8 5 1 5 2 3 1 8 6 1 2 9 2 4 10 6 10 3 6 7 10 4 7 10 7\n"
    "10 4 7 8 10 6 4 2 3 5 10 5 10 10 10 3 10 2 6 9 10 10 10 5 2 9 8 9 7 8 10 2 4 6 7 10 5 1 3 1 1 8 1 10 10 4 7 9 10 3 6 10\n"
    "5 4 10 10 6 3 7 4 6 1 8 10 2 10 10 5 6 2 10 8 3 3 10 7 10 1 10 5 10 10 9 2 3 9 4 7 8 6 10 2 7 10 9 10 1 9 10 5 10 1 4 8\n"
    "2 7 8 3 8 10 6 5 7 10 10 1 4 10 2 7 5 7 10 10 6 10 10 10 10 6 4 2 10 4 8 2 10 9 3 4 10 9 3 9 10 10 1 1 5 6 1 9 3 10 5 8\n"
    "10 3 10 1 5 6 10 1 10 10 7 9 10 10 1 4 10 7 5 7 2 2 5 8 10 10 4 9 6 10 10 1 8 2 4 7 10 10 8 6 3 8 10 10 2 3 6 3 9 4 5 9\n"
    "7 10 6 4 1 4 10 10 9 6 5 10 1 8 10 8 10 7 10 9 10 3 3 4 6 10 10 5 10 7 10 2 6 8 8 10 3 4 2 10 10 10 2 7 9 5 1 9 1 2 3 5\n"
    "10 6 3 8 4 6 5 10 6 9 10 8 7 7 7 3 1 9 1 10 10 10 2 10 3 2 6 8 10 10 10 4 10 5 2 10 2 1 10 8 7 4 10 10 5 9 9 1 3 4 5 10\n"
    "10 10 7 3 10 2 3 1 10 6 5 10 4 8 3 10 6 10 4 10 7 1 7 6 9 8 9 9 10 10 10 4 3 4 10 6 2 5 10 2 8 5 10 1 2 5 9 7 8 1 10 10\n"
    "10 2 5 1 10 3 3 4 10 1 5 10 9 10 10 2 5 7 8 10 10 6 2 10 7 7 8 10 3 10 4 2 5 1 1 10 10 8 7 10 6 10 4 10 8 9 6 4 6 3 9 9\n"
    "7 2 3 8 7 4 5 1 6 8 6 10 4 10 10 5 1 2 9 5 10 5 10 10 10 9 9 7 10 2 6 7 1 2 6 10 10 10 9 10 10 10 4 3 4 10 3 1 8 3 8 10\n"
    "8 2 6 5 10 1 10 2 10 7 8 10 3 8 10 10 10 9 2 5 10 10 1 6 8 7 7 2 9 4 5 6 6 10 10 3 3 1 4 10 9 1 5 9 10 3 4 7 10 10 4 10\n"
    "10 10 10 10 10 7 10 10 6 7 4 10 5 6 1 4 7 10 8 8 6 2 5 7 4 2 1 3 1 10 10 3 9 4 10 10 3 9 9 3 2 5 1 10 8 10 6 8 2 5 9 10\n"
    "10 6 10 10 1 8 2 3 8 1 9 10 3 9 10 10 9 10 10 4 10 8 10 8 6 7 10 10 2 10 4 7 7 3 6 10 2 10 2 5 7 1 6 1 5 9 10 3 4 5 4 5\n"
    "5 7 1 10 3 10 6 7 10 5 10 6 10 9 1 9 4 10 3 8 9 6 10 2 10 7 10 5 2 10 10 8 3 10 2 4 2 10 9 1 3 8 10 10 1 4 5 6 10 8 4 7\n"
    "9 10 10 10 7 8 8 7 5 10 9 10 4 10 2 10 10 6 8 9 1 7 1 6 3 2 3 10 10 7 10 2 4 10 3 6 8 10 6 9 2 1 4 1 3 5 10 5 10 4 5 10\n"
    "4 10 10 7 9 8 7 1 2 2 9 8 6 5 9 4 5 3 10 10 5 1 10 10 1 10 9 2 10 10 8 7 1 3 2 10 3 7 3 10 4 6 10 8 10 10 4 6 10 10 5 6\n"
    "3 1 1 7 5 10 10 10 10 2 10 6 2 2 10 2 10 9 10 7 10 10 9 10 4 5 5 7 5 4 10 9 10 4 8 10 1 4 3 10 6 8 10 1 3 3 6 8 6 7 8 9\n"
    "6 9 10 7 4 7 10 3 10 5 10 10 3 8 6 10 8 10 10 5 2 7 3 1 10 10 4 5 2 10 2 4 9 8 9 1 10 3 10 4 9 6 7 10 6 2 8 1 10 5 10 1\n"
    "7 8 10 4 10 3 10 5 1 4 1 1 9 8 1 5 2 5 10 10 6 3 7 5 7 6 10 3 9 10 10 8 4 10 10 6 8 10 3 10 10 10 10 10 2 2 6 9 2 4 7 9\n"
    "8 4 6 1 6 10 7 10 10 2 10 10 10 8 4 4 10 10 6 5 9 1 3 7 3 10 2 3 10 10 2 8 10 4 9 8 9 5 10 2 7 1 6 10 1 5 7 9 3 5 10 10\n"
    "9 10 10 7 8 2 3 8 3 5 2 6 10 10 10 3 4 10 4 6 10 1 5 2 3 10 9 10 4 4 10 1 6 9 10 7 10 10 1 1 5 8 2 5 7 10 10 6 7 8 9 10\n"
    "10 10 2 10 7 1 6 3 10 9 10 1 7 8 1 4 10 5 10 10 5 10 5 5 9 2 3 4 8 3 7 7 9 3 6 10 4 10 8 10 1 6 2 2 10 4 10 8 10 10 6 9\n"
    "8 6 5 9 6 4 10 1 10 10 7 10 4 10 10 7 10 5 6 10 2 10 7 3 2 7 3 8 10 10 10 3 1 10 9 3 5 6 8 9 8 2 4 1 2 4 9 10 5 10 1 10\n"
    "7 3 4 10 9 2 7 10 3 8 5 2 8 10 9 2 4 9 6 10 10 2 8 10 1 9 5 5 10 10 1 4 10 3 1 6 5 1 10 6 10 10 10 8 7 10 4 7 3 6 10 10\n"
    "10 1 5 10 10 2 10 7 1 6 10 10 2 2 4 4 2 3 7 10 10 3 10 8 8 8 9 4 5 10 7 1 7 10 9 9 3 4 1 10 10 10 10 6 6 5 6 5 9 3 10 8\n"
    "10 10 6 10 10 8 2 10 10 7 8 6 7 4 9 10 4 3 2 9 10 3 8 3 10 4 3 9 7 10 2 1 10 10 5 10 6 5 2 4 5 10 1 6 8 9 1 5 1 7 10 10\n"
    "10 6 10 10 7 5 6 10 3 10 10 1 3 10 7 3 3 2 8 10 10 10 5 6 10 4 8 7 4 6 1 1 8 7 9 2 9 1 10 8 5 10 2 10 4 9 10 5 9 2 4 10\n"
    "7 3 5 1 10 10 7 1 9 7 10 4 9 10 3 2 10 3 10 8 8 1 6 10 2 10 5 10 8 2 10 10 6 5 6 10 10 9 7 9 1 8 10 5 10 6 4 4 2 3 4 10\n"
    "6 6 1 10 10 10 7 10 4 10 4 10 10 8 10 2 4 3 9 2 3 10 10 5 3 5 2 8 10 9 7 1 3 10 1 10 6 1 6 9 8 10 2 7 5 4 5 7 8 9 10 10\n"
    "10 7 1 10 4 6 1 5 7 10 9 3 7 8 8 2 9 2 10 3 10 9 6 7 8 2 6 4 10 10 1 3 5 10 1 3 10 5 10 4 8 5 10 10 4 10 9 10 10 10 2 6\n"
    "8 6 2 8 5 6 7 10 2 4 6 3 10 10 10 8 3 10 9 10 10 8 7 2 10 10 6 4 1 4 5 9 10 3 10 5 1 1 9 10 10 10 10 3 7 9 1 2 5 4 7 10\n"
    "7 6 8 10 6 9 6 1 10 4 10 2 8 10 10 4 10 3 9 10 10 3 3 10 10 8 5 2 8 10 5 2 7 9 4 5 10 10 7 3 5 10 1 10 4 9 1 2 10 1 6 7\n"
    "2 5 10 6 6 2 4 8 5 10 3 3 4 7 10 1 10 1 1 10 8 10 3 9 2 8 5 10 10 4 7 10 5 7 10 6 10 2 10 1 10 6 10 3 9 8 7 9 4 9 10 10\n"
    "4 2 10 4 10 8 9 3 10 6 10 10 2 10 5 10 7 3 7 5 6 10 7 10 10 1 7 5 8 6 5 1 10 10 9 8 4 4 10 10 8 9 3 2 2 10 10 1 3 1 6 9\n"
    "8 10 6 5 8 10 2 8 9 2 10 2 7 1 4 1 3 1 4 5 9 8 10 5 9 4 10 10 10 6 4 9 1 6 10 10 10 2 10 5 7 10 6 3 7 3 10 7 10 10 10 3\n"
    "7 7 4 9 4 8 10 2 5 10 6 10 6 10 8 1 10 2 1 3 10 9 10 1 8 5 2 5 7 10 10 1 6 6 8 10 2 3 10 9 7 10 10 4 10 4 3 9 10 5 10 3\n"
    "1 10 8 9 5 1 6 10 10 10 2 10 3 9 8 9 7 5 10 6 6 1 3 10 6 5 2 4 10 7 10 7 4 10 7 2 10 10 2 10 4 8 8 9 4 1 10 3 10 10 3 5\n"
    "8 10 4 10 4 10 9 10 3 5 8 6 1 1 1 1 9 9 7 7 5 8 10 6 5 2 3 7 2 10 6 10 10 2 5 10 8 4 10 10 10 10 2 6 3 10 10 3 4 10 7 9\n"
    "4 10 10 8 10 2 2 7 6 2 10 8 4 9 10 2 10 10 1 10 8 9 10 3 9 10 10 5 10 5 10 6 4 10 3 7 7 3 6 6 10 5 5 1 9 3 4 7 8 1 1 10\n"
    "4 10 8 2 10 10 7 1 2 6 5 8 7 10 4 5 10 3 10 10 9 9 10 3 2 10 6 10 1 5 2 4 5 1 9 8 10 1 3 7 6 8 10 10 3 4 9 10 6 7 10 10\n"
    "6 9 8 7 3 10 10 4 4 5 10 10 2 10 10 7 10 7 3 10 4 10 6 9 5 10 10 8 5 1 9 9 7 8 1 3 1 10 6 10 2 6 10 1 5 10 3 8 2 10 2 4\n"
    "5 4 10 2 10 3 10 8 8 10 9 10 7 1 10 10 5 3 8 6 10 10 5 1 6 9 3 10 10 10 10 9 4 3 7 2 8 2 4 6 6 10 9 7 10 2 1 7 1 5 4 10\n"
    "4 2 10 10 5 7 3 9 10 4 10 10 8 3 7 8 9 10 3 10 10 2 4 6 5 2 10 6 9 5 8 10 9 7 1 6 5 10 10 6 8 7 4 1 10 2 1 10 10 10 1 3\n"
    "4 10 8 9 5 7 10 3 10 1 7 5 2 3 2 2 10 6 8 10 1 1 10 10 5 10 6 8 10 10 3 10 7 9 10 4 3 4 5 1 8 10 6 4 6 9 2 9 10 10 7 10\n"
    "1 1 3 10 4 3 10 6 2 4 10 10 8 5 10 10 10 10 10 10 9 7 10 9 3 8 6 5 9 10 7 10 8 10 5 2 4 2 9 7 10 7 10 3 8 6 4 1 2 6 1 5\n"
    "10 10 8 7 10 4 2 9 9 1 5 10 8 10 2 6 5 7 3 10 9 6 1 8 10 7 10 10 4 2 4 1 9 10 10 7 5 1 2 10 3 8 10 6 3 5 6 10 10 10 3 4\n"
    "3 6 5 3 1 10 10 2 1 2 10 10 4 1 9 1 10 10 8 7 8 5 4 7 5 9 10 10 9 4 10 6 4 6 5 10 10 2 10 10 6 10 3 3 8 7 7 9 10 2 8 10\n"
    "6 4 6 10 9 7 10 10 4 4 8 10 10 3 10 3 2 6 1 5 5 5 10 10 10 9 1 5 8 10 8 10 10 7 2 7 9 1 10 8 2 4 1 9 10 3 6 10 10 2 3 7\n"
    "10 10 10 4 6 7 10 7 9 7 5 10 1 10 4 10 1 5 10 2 3 10 9 3 2 8 3 10 10 10 2 4 9 5 4 8 7 10 6 8 1 9 10 6 10 5 6 10 1 2 3 8\n"
    "6 7 6 2 7 5 1 4 4 9 10 1 3 10 3 1 10 10 5 2 10 10 8 10 10 4 9 4 9 5 2 2 6 8 10 8 10 3 5 6 10 10 3 7 9 8 10 1 7 10 10 10\n"
    "0\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ(
          "Win : 243\n"
          "Loss: 187\n"
          "Loss: 127\n"
          "Loss: 85\n"
          "Loss: 244\n"
          "Loss: 205\n"
          "Loss: 259\n"
          "Loss: 169\n"
          "Loss: 160\n"
          "Loss: 97\n"
          "Loss: 481\n"
          "Loss: 142\n"
          "Loss: 115\n"
          "Loss: 169\n"
          "Loss: 103\n"
          "Loss: 100\n"
          "Loss: 202\n"
          "Loss: 121\n"
          "Loss: 136\n"
          "Loss: 115\n"
          "Loss: 103\n"
          "Loss: 148\n"
          "Loss: 268\n"
          "Loss: 190\n"
          "Loss: 193\n"
          "Loss: 118\n"
          "Loss: 169\n"
          "Loss: 94\n"
          "Loss: 106\n"
          "Loss: 214\n"
          "Loss: 139\n"
          "Loss: 118\n"
          "Loss: 124\n"
          "Loss: 91\n"
          "Loss: 118\n"
          "Loss: 79\n"
          "Loss: 109\n"
          "Loss: 163\n"
          "Loss: 142\n"
          "Loss: 109\n"
          "Loss: 109\n"
          "Loss: 109\n"
          "Draw: 259\n"
          "Loss: 169\n"
          "Loss: 241\n"
          "Loss: 166\n"
          "Loss: 100\n"
          "Loss: 112\n"
          "Loss: 97\n"
          "Loss: 118\n"
          "Loss: 139\n"
          "Loss: 85\n"
          "Loss: 103\n"
          "Loss: 115\n"
          "Loss: 103\n"
          "Loss: 193\n"
          "Loss: 226\n"
          "Loss: 139\n",
          oss.str());
}

#endif
