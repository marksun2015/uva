#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include "uva263.h"

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

unsigned int mapping_str_order_to_int(string &input_str, int order_type) {
  if (order_type == ASCENDING)
    sort(input_str.begin(), input_str.end(), less<int>());
  if (order_type == DESCENDING)
    sort(input_str.begin(), input_str.end(), greater<int>());

  return stoi(input_str);
}

void resolve_uva263(string &input_str) {
  unsigned int descending_number = 0;
  unsigned int ascending_number = 0;
  unsigned int difference = 0;
  unsigned int input_integer = stoi(input_str);
  int chain_len = 0;

  cout << "Original number was " << input_integer << endl;
  while (1) {
    input_str = to_string(input_integer);
    descending_number = mapping_str_order_to_int(input_str, DESCENDING);
    ascending_number = mapping_str_order_to_int(input_str, ASCENDING);
    difference = descending_number - ascending_number;
    cout << descending_number << " - " << ascending_number << " = "
         << difference << endl;
    chain_len++;

    if (input_integer != difference)
      input_integer = difference;
    else
      break;
  }
  cout << "Chain length " << chain_len << endl;
}

int main(int argc, char **argv) {
#ifdef ONLINE_JUDGE
  string input_str;
  cin >> input_str;
  cout << endl;
  resolve_uva263(input_str);
  return 0;
#else
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}
