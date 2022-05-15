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
    Hand: 3D 5S 2H QD TD Deck: 6S KH 9H AD QH Best hand: highest-car
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <memory>

using namespace std;

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif


/*
 *
 *    "straight-flush"
 *    "four-of-a-kind" 
 *    "full-house"   
 *    "flush"   
 *    "straight"   
 *    "three-of-a-kind"  
 *    "two-pairs"  
 *    "one-pair"   
 *    "highest-card" 
 *   A2345 < 23456 < 34567 < ... < TJQKA  
 */
struct Card {
    int value;
    int color;
};

class Poker {
  public:
    explicit Poker(std::string input);
    ~Poker()=default;
    
    void changeCards(int change_card_numbers);

  private:
    std::queue <std::string> hand_card_;
    std::queue <std::string> desk_card_;
    std::vector <Card> card_in_hand_;
    std::vector <Card> card_in_desk_;
};

Poker::Poker(std::string input) {

  int pos;
  //std::cout << "Hand:";
  for (int i=0; i<5; i++) {
    pos = input.find(' ');
    //std::cout << " "  << input.substr(0, pos);
    hand_card_.push(input.substr(0, pos));  
    input.erase (0, pos+1);
  }
  
  std::cout << " Desk:";
  for (int i=0; i<5; i++) {
    pos = input.find(' ');
    std::cout << " "  << input.substr(0, pos);
    desk_card_.push(input.substr(0, pos));  
    input.erase (0, pos+1);
  }
}

void Poker::changeCards(int change_card_numbers){
  //int pos = 0;
  std::queue <std::string> possible_card;

  //possible_card =  

}

#if 0
void listCards(std::string input, std::string output, std::ostream &os) {
  int pos = 0;
  std::queue <std::string> hand;
  std::queue <std::string> deck;

  std::cout << "Hand:";
  for (int i=0; i<5; i++) {
    pos = input.find(' ');
    std::cout << " "  << input.substr(0, pos);
    hand.push(input.substr(0, pos));  
    input.erase (0, pos+1);
  }
  
  std::cout << " Desk:";
  for (int i=0; i<5; i++) {
    pos = input.find(' ');
    std::cout << " "  << input.substr(0, pos);
    hand.push(input.substr(0, pos));  
    input.erase (0, pos+1);
  }
 
  //if(failed)
  //  os << "No" << std::endl; 
  //else
  //  os << "Yes" << std::endl;
}
#endif

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string input;
  std::string output;
  int i,j;

  while (getline(is, input)) {
 
  if (input.empty()) {
    break;
  }

  os << "Hand:";
  for (i = 0; i < 5; i++) {
    os << " "  << input.substr(0+i*3, 2);
  }
  
  os << " Desk:";
  for (j=i; j < 10; j++) {
    os << " "  << input.substr(0+j*3, 2);
  }

  std::shared_ptr<Poker> poker = std::make_shared<Poker>(input);
  {
        //for(int i=0 ;i<=5 ;i++)
        //    card->changeCards(i);
  }
    //std::cout << "input "  << input << std::endl; 
    //listCards(input, output, os);
   // maximizeValue();  
    std::cout << std::endl;

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
TEST(uva514, test_string1) {
  std::istringstream iss(
            "10\n"
            "5 7 10 9 8 6 4 3 2 1\n"
            "5 6 4 8 7 3 2 9 1 10\n"
            "0\n"
            "0\n");

  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("Yes\n"
            "Yes\n"
            "\n",
            oss.str());
}
#endif

#if 0
#include <iostream>
#include <vector>

using namespace std;

vector<int> hand_card;
vector<int> possible_card;

void pretty_print(const vector<int>& v, int number) {
  static int count = 0;
  //cout << "possible_card: " << (++count) << " ";  // << ": [ ";
  for (int i = 0; i < v.size(); ++i) 
  { 
      cout << v[i] << " "; 
  }

  for (int i = 0; i < number; i++) {
      cout << "c " ; 
  }
  //cout << "] " << endl;
  cout << endl;
}

//ref: https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c  
void comb_max_value(int offset, int k, int number) {
  if (k == 0) {
    pretty_print(possible_card,number);
    return;
  }

  for (int i = offset; i <= hand_card.size() - k; i++) {
    possible_card.push_back(hand_card[i]);
    comb_max_value(i+1, k-1, number);
    possible_card.pop_back();
  }
}

int main() {
  int n = 5, k = 3;

  for (int i = 1; i <= n; i++) {
      hand_card.push_back(i);
  
  }

  for (int k = 0; k <= 5; k++) { 
      comb_max_value(0, k, 5-k);
  }
  return 0;
}
#endif
