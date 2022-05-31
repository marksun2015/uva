#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// https://www.wikiwand.com/zh/%E6%92%B2%E5%85%8B%E7%89%8C%E5%9E%8B
//
// 1.highest-card：散牌，沒有以上牌型。
// 2.one-pair：對子，牌面有一個對子，即2個同值
// 3.two-pairs：兩對，牌面有2個對子
// 4.three-of-a-kind：三條，牌面有3個相同的值
// 5.straight：順子，五張牌的值連續，A可以作為1也可以作為14
// 6.flush：同花，五張牌的花色相同，不是同花順
// 7.full-house：葫蘆，牌面有3個相同值，剩下2個也相同值
// 8.four-of-a-kind：鐵支，牌面有4個相同的值
// 9.straight-flush：同花順，牌面為T（10） - A，這裡不論花色是否相同

enum PokerType {
  HighestCard = 1,
  OnePair = 2,
  TwoPairs = 3,
  ThreeOfAKind = 4,
  Straight = 5,
  Flush = 6,
  FullHouse = 7,
  FourOfAKind = 8,
  StraightFlush = 9,
};

class Card {
 public:
  Card(const std::string& str = "") {
    point = ToPoint(str[0]);
    suit = str[1];
  }

  int point;
  char suit;

  bool operator==(const Card& rhs) {
    return (point == rhs.point && suit == rhs.suit);
  }

  bool operator<(const Card& rhs) const { return point < rhs.point; }

 private:
  int ToPoint(char c) {
    switch (c) {
      case 'A':
        return 1;
      case 'T':
        return 10;
      case 'J':
        return 11;
      case 'Q':
        return 12;
      case 'K':
        return 13;
    }
    return c - '0';
  }
};

int cur;
Card hand[5], deck[5], sum[32][5], temp[5];

// 32 =
// C(5, 0) = 1
// C(5, 1) = 5
// C(5, 2) = 10
// C(5, 3) = 10
// C(5, 4) = 5
// C(5, 5) = 1
void GeneratePockers(int X, int cur1, int cur2, Card* hand, Card* deck) {
  if (X == 0) {
    for (int i = cur2; i < 5; i++)
      temp[i] = deck[i - cur2];
    memcpy(sum[cur++], temp, sizeof(Card) * 5);
    return;
  }

  for (int i = cur1; i <= 5 - X; i++) {
    temp[cur2] = hand[i];
    GeneratePockers(X - 1, i + 1, cur2 + 1, hand, deck);
  }
}

bool IsStraight(Card cards[]) {
  if (cards[4].point - cards[3].point == 1 &&
          cards[3].point - cards[2].point == 1 &&
          cards[2].point - cards[1].point == 1 &&
          cards[1].point - cards[0].point == 1 ||
      cards[0].point == 1 && cards[1].point == 10 && cards[2].point == 11 &&
          cards[3].point == 12 && cards[4].point == 13)
    return true;
  return false;
}

bool IsFlush(Card cards[]) {
  for (int i = 1; i < 5; i++)
    if (cards[i].suit != cards[0].suit)
      return false;
  return true;
}

int Judge(Card* temp) {
  std::sort(temp, temp + 5);

  bool straight = IsStraight(temp);
  bool flush = IsFlush(temp);

  if (flush && straight)
    return StraightFlush;

  int count[14] = {0}, four = 0, three = 0, two = 0;

  for (int i = 0; i < 5; i++)
    count[temp[i].point]++;

  for (int i = 1; i <= 13; i++)
    if (count[i] > 1) {
      if (count[i] == 2)
        two++;
      else if (count[i] == 3)
        three++;
      else
        four++;
    }

  if (four)
    return FourOfAKind;
  if (three && two)
    return FullHouse;
  if (flush)
    return Flush;
  if (straight)
    return Straight;
  if (three)
    return ThreeOfAKind;
  if (two == 2)
    return TwoPairs;
  if (two)
    return OnePair;

  return HighestCard;
}

std::string ToPokerTypeStr(int best) {
  switch (best) {
    case HighestCard:
      return "highest-card";
    case OnePair:
      return "one-pair";
    case TwoPairs:
      return "two-pairs";
    case ThreeOfAKind:
      return "three-of-a-kind";
    case Straight:
      return "straight";
    case Flush:
      return "flush";
    case FullHouse:
      return "full-house";
    case FourOfAKind:
      return "four-of-a-kind";
    case StraightFlush:
      return "straight-flush";
  }
  return "";  // FIXME: should throw error here
}

void Solution(std::istream& cin) {
  std::string tmp;
  while (cin >> tmp) {
    std::cout << "Hand: ";
    std::cout << tmp << ' ';

    hand[0] = Card(tmp);

    for (int i = 1; i < 5; i++) {
      cin >> tmp;
      std::cout << tmp << ' ';
      hand[i] = Card(tmp);
    }

    std::cout << "Deck: ";
    for (int i = 0; i < 5; i++) {
      cin >> tmp;
      std::cout << tmp << ' ';
      deck[i] = Card(tmp);
    }

    cur = 0;

    for (int i = 0; i <= 5; i++)
      GeneratePockers(i, 0, 0, hand, deck);

    int best = 0;
    for (int i = 0; i < 32; i++) {
      int t = Judge(sum[i]);
      if (t > best)
        best = t;

      if (best == 9)
        break;
    }

    std::cout << "Best hand: " << ToPokerTypeStr(best) << std::endl;
  }
}

#if !defined(GTEST_TEST)
int main(int argc, char* argv[]) {
  Solution(std::cin);
  return 0;
}
#endif  // !defind(GTEST_TEST)
