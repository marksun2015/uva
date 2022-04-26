#include <bits/stdc++.h>
#include <boost/format.hpp>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

using namespace std;

class Time {
public:
  Time(int _hours, int _minutes) : hours(_hours), minutes(_minutes) {}

  bool operator>(const Time &t) const {
    return ((hours - t.hours) * 60 + minutes - t.minutes > 0) ? true : false;
  }
  Time operator-(const Time &t) const {
    int64_t diff = (hours - t.hours) * 60 + minutes - t.minutes;
    return Time(diff / 60, diff % 60);
  }
  friend std::ostream &operator<<(std::ostream &os, const Time &t) {
    string text = str(boost::format("%02d:%02d") % t.hours % t.minutes);
    os << text;
    return os;
  }
  string print_text_time() {
    const string hours_text =
        (hours > 0) ? to_string(hours) + " hours and " : "";
    return hours_text + to_string(minutes) + " minutes.";
  }

private:
  int hours;
  int minutes;
};

class Time_set {
public:
  Time_set(Time _start_time, Time _end_time)
      : start_time(_start_time), end_time(_end_time),
        interval(_end_time - _start_time) {}

  Time start_time;
  Time end_time;
  Time interval;
};

bool read_daily_to_work_list(std::istream &is,
                             vector<Time_set> &work_time_list) {
  int num;
  string line;
  int start_hours, start_minutes, end_hours, end_minutes;

  if (!getline(is, line))
    return false;

  work_time_list.clear();
  num = stoi(line);

  for (auto i = 0; i < num; i++) {
    getline(is, line);
    sscanf(line.c_str(), "%d:%d %d:%d", &start_hours, &start_minutes,
           &end_hours, &end_minutes);
    work_time_list.push_back(
        Time_set({start_hours, start_minutes}, {end_hours, end_minutes}));
  }
  return true;
}

void compute_nap_time(vector<Time_set> &work_time_list,
                      vector<Time_set> &nap_time_list) {
  Time last_work_end_time{10, 0};
  Time get_off_time{18, 0};
  nap_time_list.clear();

  sort(work_time_list.begin(), work_time_list.end(),
       [](auto &lt, auto &rt) { return (rt.start_time > lt.start_time); });

  /* two case to find nap time */
  /* case 1: current work start time > last work end time */
  /* case 2: get off time > last work end time */
  for (auto &current : work_time_list) {
    if (current.start_time > last_work_end_time)
      nap_time_list.push_back({last_work_end_time, current.start_time});

    last_work_end_time = current.end_time;
  }
  if (get_off_time > last_work_end_time)
    nap_time_list.push_back({last_work_end_time, get_off_time});
}

Time_set find_the_longest_nap_time(vector<Time_set> &nap_time_list) {
  auto max = *std::max_element(
      nap_time_list.begin(), nap_time_list.end(),
      [](auto &lt, auto &rt) { return (rt.interval > lt.interval); });

  return max;
}

void print_the_longest_nap_time(std::ostream &os, int day, Time_set &nap) {
  os << "Day #" << day << ": the longest nap starts at " << nap.start_time
     << " and will last for " << nap.interval.print_text_time() << endl;
}

void resolve_uva(std::istream &is, std::ostream &os) {
  vector<Time_set> work_time_list;
  vector<Time_set> nap_time_list;
  int day = 1;

  while (1) {
    if (read_daily_to_work_list(is, work_time_list) == false)
      break;

    compute_nap_time(work_time_list, nap_time_list);
    Time_set nap = find_the_longest_nap_time(nap_time_list);
    print_the_longest_nap_time(os, day, nap);
    day++;
  }
}

int main(int argc, char **argv) {
#ifdef ONLINE_JUDGE
  resolve_uva(cin, cout);
  return 0;
#else
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}