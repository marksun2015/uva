/*
uva131

    In 5-card draw poker, a player is dealt a hand of five cards (which may be looked at). The player may
    then discard between zero and five of his or her cards and have them replaced by the same number of
    cards from the top of the deck (which is face down). The object is to maximize the value of the final
    hand. The different values of hands in poker are given at the end of this problem.
      Normally the player cannot see the cards in the deck and so must use probability to decide which
    cards to discard. In this problem, we imagine that the poker player is psychic and knows which cards
    are on top of the deck. Write a program which advises the player which cards to discard so as to
    maximize the value of the resulting hand.
    
    Input
    Input will consist of a series of lines, each containing the initial five cards in the hand then the first
    five cards on top of the deck. Each card is represented as a two-character code. The first character
    is the face-value (A=Ace, 2–9, T=10, J=Jack, Q=Queen, K=King) and the second character is the suit
    (C=Clubs, D=Diamonds, H=Hearts, S=Spades). Cards will be separated by single spaces. Each input
    line will be from a single valid deck, that is there will be no duplicate cards in each hand and deck.
    
    Output
    Each line of input should produce one line of output, consisting of the initial hand, the top five cards
    on the deck, and the best value of hand that is possible. Input is terminated by end of file.
    
    Note: Use the sample input and output as a guide.
      Note that the order of the cards in the player’s hand is irrelevant, but the order of the cards in the
    deck is important because the discarded cards must be replaced from the top of the deck. Also note
    that examples of all types of hands appear in the sample output, with the hands shown in decreasing
    order of value.
    
    Sample Input
    TH JH QC QD QS QH KH AH 2S 6S
    2H 2S 3H 3S 3C 2D 3D 6C 9C TH
    2H 2S 3H 3S 3C 2D 9C 3D 6C TH
    2H AD 5H AC 7H AH 6H 9H 4H 3C
    AC 2D 9C 3S KD 5S 4D KS AS 4C
    KS AH 2H 3C 4H KC 2C TC 2D AS
    AH 2C 9S AD 3C QH KS JS JD KD
    6C 9C 8C 2D 7C 2H TC 4C 9S AH
    3D 5S 2H QD TD 6S KH 9H AD QH

    Sample Output
    Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush
    Hand: 2H 2S 3H 3S 3C Deck: 2D 3D 6C 9C TH Best hand: four-of-a-kind
    Hand: 2H 2S 3H 3S 3C Deck: 2D 9C 3D 6C TH Best hand: full-house
    Hand: 2H AD 5H AC 7H Deck: AH 6H 9H 4H 3C Best hand: flush
    Hand: AC 2D 9C 3S KD Deck: 5S 4D KS AS 4C Best hand: straight
    Hand: KS AH 2H 3C 4H Deck: KC 2C TC 2D AS Best hand: three-of-a-kind
    Hand: AH 2C 9S AD 3C Deck: QH KS JS JD KD Best hand: two-pairs
    Hand: 6C 9C 8C 2D 7C Deck: 2H TC 4C 9S AH Best hand: one-pair
    Hand: 3D 5S 2H QD TD Deck: 6S KH 9H AD QH Best hand: highest-card
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

enum MaxValue {
  HighestCard = 0,
  OnePair,
  TwoPairs,
  ThreeOfAKind,
  Straight,
  Flush,
  FullHouse,
  FourOfAKind,
  StraightFlush
};

struct CardNode {
  int value;
  int color;
};

class Poker {
public:
  explicit Poker(std::string input);
  ~Poker() = default;

  void InitCards(std::string node);
  void CombMaxValue(int offset, int k, int number);
  CardNode MappingCards(std::string node);
  void ChangeCards(const vector<int> &hand_number, int number);
  void CheckMaxValue();
  void InitHandcard(int number);
  std::string GetMaxValue(void);
  static bool Cmp(CardNode x, CardNode y);

private:
  std::vector<CardNode> card_in_hand_;
  std::vector<CardNode> card_in_deck_;
  std::vector<CardNode> card_possible_;
  std::vector<int> card_position_;
  std::vector<int> combination_;
  std::map<int, string> mapValue;
  int max_value_;
};

Poker::Poker(std::string input) : max_value_(0) {
  mapValue[HighestCard] = "highest-card";
  mapValue[OnePair] = "one-pair";
  mapValue[TwoPairs] = "two-pairs";
  mapValue[ThreeOfAKind] = "three-of-a-kind";
  mapValue[Straight] = "straight";
  mapValue[Flush] = "flush";
  mapValue[FullHouse] = "full-house";
  mapValue[FourOfAKind] = "four-of-a-kind";
  mapValue[StraightFlush] = "straight-flush";
}

void Poker::InitHandcard(int number) {
  for (int i = 0; i < number; i++)
    card_position_.push_back(i);
}

bool Poker::Cmp(CardNode x, CardNode y) {
  if (x.value != y.value)
    return x.value < y.value;
  return x.value < y.value;
}

void Poker::CheckMaxValue() {
  int straight = 0;
  int same_c = 0;
  int same_d = 0;
  int same_h = 0;
  int same_s = 0;

  int number[14] = {0}; // use number[1] ~ number[13]
  int current_max = HighestCard;

  std::sort(card_possible_.begin(), card_possible_.end(), Cmp);

  // for (long unsigned int i = 0; i < card_possible_.size() ; i++)
  //  std::cout << " v: " << card_possible_[i].value; //<< " c: " <<
  //  card_possible_[i].color ;
  // std::cout << std::endl;

  for (long unsigned int i = 0; i < (card_possible_.size() - 1); i++) {
    if ((card_possible_[i].value + 1) == card_possible_[i + 1].value)
      straight++;
  }

  if (straight == 4) {
    if (current_max < Straight)
      current_max = Straight;
  }

  if ((card_possible_[0].value == 1) && (card_possible_[1].value == 10) &&
      (card_possible_[2].value == 11) && (card_possible_[3].value == 12) &&
      (card_possible_[4].value == 13)) {
    if (current_max < Straight)
      current_max = Straight;
  }

  for (long unsigned int i = 0; i < card_possible_.size(); i++) {
    if ((card_possible_[i].color) == 1)
      same_c++;
    if ((card_possible_[i].color) == 2)
      same_d++;
    if ((card_possible_[i].color) == 3)
      same_h++;
    if ((card_possible_[i].color) == 4)
      same_s++;
    number[card_possible_[i].value]++;
  }

  if ((same_c == 5) || (same_d == 5) || (same_h == 5) || (same_s == 5)) {
    if (current_max == Straight)
      current_max = StraightFlush;

    if (current_max < Flush)
      current_max = Flush;
  }

  for (int i = 1; i < 14; i++) {
    if (number[i] == 4) {
      if (current_max < FourOfAKind)
        current_max = FourOfAKind;
    } else if (number[i] == 3) {
      if (current_max == OnePair)
        current_max = FullHouse;

      if (current_max < ThreeOfAKind)
        current_max = ThreeOfAKind;
    } else if (number[i] == 2) {
      if (current_max == ThreeOfAKind)
        current_max = FullHouse;

      if (current_max == OnePair)
        current_max = TwoPairs;

      if (current_max < OnePair)
        current_max = OnePair;
    }
  }

  if (current_max > max_value_)
    max_value_ = current_max;

  card_possible_.clear();
}

void Poker::ChangeCards(const vector<int> &hand_number, int number) {
  CardNode card_node;

  for (long unsigned int i = 0; i < hand_number.size(); i++) {
    card_node = card_in_hand_[hand_number[i]];
    card_possible_.push_back(card_node);
  }

  for (int i = 0; i < number; i++) {
    card_node = card_in_deck_[i];
    card_possible_.push_back(card_node);
  }
}

/*
ref: https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c

ex:範例C5取3                        C 5取3。     n為2：代表要換掉桌面牌數2張
遞迴第一層，拆成三組相加            遞迴展開
comb({ 1 2 3 4 5 }, 3) =            CombMaxValue(0,3,n)
{ 1, comb({ 2 3 4 5 }, 2) } and        ├──CombMaxValue(1,2,n)            push 1
{ 2, comb({ 3 4 5 }, 2) } and          │   ├──CombMaxValue(2,1,n)           push 2
{ 3, comb({ 4 5 }, 2) }                │   │    ├──CombMaxValue(3,0,n)         push 3 (1, 2, 3)
                                       │   │    ├──CombMaxValue(4,0,n)         push 4 (1, 2, 4)
                                       │   │    └──CombMaxValue(5,0,n)         push 5 (1, 2, 5)
 可能性如下                            │   ├──CombMaxValue(3,1,n)           push 3
  第一組                               │   │    ├──CombMaxValue(4,0,n)         push 4 (1, 3, 4)
  1  2  3                              │   │    └──CombMaxValue(5,0,n)         push 5 (1, 3, 5)
  1  2  4                              │   └──CombMaxValue(4,1,n)           push 4
  1  2  5                              │        └──CombMaxValue(5,0,n)         push 5 (1, 4, 5)
  1  3  4                              ├──CombMaxValue(2,2,n)            push 2
  1  3  5                              │   ├──CombMaxValue(3,1)             push 3
  1  4  5                              │   │    ├──CombMaxValue(4,0,n)         push 4 (2, 3, 4)
  第二組                               │   │    └──CombMaxValue(5,0,n)         push 5 (2, 3, 5)
  2  3  4                              │   └──CombMaxValue(4,1)             push 4
  2  3  5                              │        └──CombMaxValue(5,0,n)         push 5 (2, 4, 5)
  2  4  5                              └──CombMaxValue(3,2,n)            push 3
  第三組                                   └──CombMaxValue(4,1,n)           push 4
  3  4  5                                       └──CombMaxValue(5,0,n)         push 5 (3, 4, 5)

*/

void Poker::CombMaxValue(int offset, int k, int number) {
  if (k == 0) {
    ChangeCards(combination_, number);
    CheckMaxValue();
    return;
  }

  for (long unsigned int i = offset; i <= (card_position_.size() - k); i++) {
    combination_.push_back(card_position_[i]);
    CombMaxValue(i + 1, k - 1, number);
    combination_.pop_back();
  }
}

CardNode Poker::MappingCards(std::string node) {
  const char *value = node.substr(0, 1).c_str();
  CardNode card_node;

  switch (*value) {
  case 'T':
    card_node.value = 10;
    break;
  case 'J':
    card_node.value = 11;
    break;
  case 'Q':
    card_node.value = 12;
    break;
  case 'K':
    card_node.value = 13;
    break;
  case 'A':
    card_node.value = 1;
    break;
  default:
    card_node.value = (int)(*value) - '0';
    break;
  }

  const char *color = node.substr(1, 1).c_str();
  ;
  switch (*color) {
  case 'C':
    card_node.color = 1;
    break;
  case 'D':
    card_node.color = 2;
    break;
  case 'H':
    card_node.color = 3;
    break;
  case 'S':
    card_node.color = 4;
    break;
  }

  return card_node;
}

void Poker::InitCards(std::string input) {
  int pos;
  CardNode card_node;

  for (int i = 0; i < 5; i++) {
    pos = input.find(' ');
    card_node = MappingCards(input.substr(0, 2));
    card_in_hand_.push_back(card_node);
    input.erase(0, pos + 1);
  }

  for (int i = 0; i < 5; i++) {
    pos = input.find(' ');
    card_node = MappingCards(input.substr(0, 2));
    card_in_deck_.push_back(card_node);
    input.erase(0, pos + 1);
  }
}

std::string Poker::GetMaxValue(void) { return mapValue[max_value_]; }

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  std::string output;
  int i, j;
  int n = 5;

  while (getline(is, input)) {
    if (input.empty()) {
      break;
    }

    os << "Hand:";
    for (i = 0; i < 5; i++) {
      os << " " << input.substr(0 + i * 3, 2);
    }

    os << " Deck:";
    for (j = i; j < 10; j++) {
      os << " " << input.substr(0 + j * 3, 2);
    }

    std::shared_ptr<Poker> poker = std::make_shared<Poker>(input);
    {
      poker->InitCards(input);
      poker->InitHandcard(5);
      // C n取i的組合情況。i=0，代表全部換掉。
      for (i = 0; i <= n; i++) {
        // 手上i張, 換掉桌上出5-i張牌
        poker->CombMaxValue(0, i, 5 - i);
      }
      os << " Best hand: " << poker->GetMaxValue() << std::endl;
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
TEST(uva131, test_string1) {
  std::istringstream iss("TH JH QC QD QS QH KH AH 2S 6S\n"
                         "2H 2S 3H 3S 3C 2D 3D 6C 9C TH\n"
                         "2H 2S 3H 3S 3C 2D 9C 3D 6C TH\n"
                         "2H AD 5H AC 7H AH 6H 9H 4H 3C\n"
                         "AC 2D 9C 3S KD 5S 4D KS AS 4C\n"
                         "KS AH 2H 3C 4H KC 2C TC 2D AS\n"
                         "AH 2C 9S AD 3C QH KS JS JD KD\n"
                         "6C 9C 8C 2D 7C 2H TC 4C 9S AH\n"
                         "3D 5S 2H QD TD 6S KH 9H AD QH\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ(
      "Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush\n"
      "Hand: 2H 2S 3H 3S 3C Deck: 2D 3D 6C 9C TH Best hand: four-of-a-kind\n"
      "Hand: 2H 2S 3H 3S 3C Deck: 2D 9C 3D 6C TH Best hand: full-house\n"
      "Hand: 2H AD 5H AC 7H Deck: AH 6H 9H 4H 3C Best hand: flush\n"
      "Hand: AC 2D 9C 3S KD Deck: 5S 4D KS AS 4C Best hand: straight\n"
      "Hand: KS AH 2H 3C 4H Deck: KC 2C TC 2D AS Best hand: three-of-a-kind\n"
      "Hand: AH 2C 9S AD 3C Deck: QH KS JS JD KD Best hand: two-pairs\n"
      "Hand: 6C 9C 8C 2D 7C Deck: 2H TC 4C 9S AH Best hand: one-pair\n"
      "Hand: 3D 5S 2H QD TD Deck: 6S KH 9H AD QH Best hand: highest-card\n",
      oss.str());
}

TEST(uva131, test_string2) {
  std::istringstream iss("2D 3D 6C 9C TH 2H 2S 3H 3S 3C\n"
                         "2D 9C 3D 6C TH 2H 2S 3H 3S 3C\n"
                         "AH 6H 9H 4H 3C 2H AD 5H AC 7H\n"
                         "5S 4D KS AS 4C AC 2D 9C 3S KD\n"
                         "KC 2C TC 2D AS KS AH 2H 3C 4H\n"
                         "QH KS JS JD KD AH 2C 9S AD 3C\n"
                         "2H TC 4C 9S AH 6C 9C 8C 2D 7C\n"
                         "6S KH 9H AD QH 3D 5S 2H QD TD\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);

  EXPECT_EQ(
      "Hand: 2D 3D 6C 9C TH Deck: 2H 2S 3H 3S 3C Best hand: full-house\n"
      "Hand: 2D 9C 3D 6C TH Deck: 2H 2S 3H 3S 3C Best hand: full-house\n"
      "Hand: AH 6H 9H 4H 3C Deck: 2H AD 5H AC 7H Best hand: flush\n"
      "Hand: 5S 4D KS AS 4C Deck: AC 2D 9C 3S KD Best hand: two-pairs\n"
      "Hand: KC 2C TC 2D AS Deck: KS AH 2H 3C 4H Best hand: three-of-a-kind\n"
      "Hand: QH KS JS JD KD Deck: AH 2C 9S AD 3C Best hand: two-pairs\n"
      "Hand: 2H TC 4C 9S AH Deck: 6C 9C 8C 2D 7C Best hand: flush\n"
      "Hand: 6S KH 9H AD QH Deck: 3D 5S 2H QD TD Best hand: one-pair\n",
      oss.str());
}
#endif
