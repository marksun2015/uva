#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

class Time {
 public:
  explicit Time(const std::string& line = "00:00") {
    strptime(line.c_str(), "%H:%M", &tm_);
  }
  ~Time() = default;

  int Hour() const { return tm_.tm_hour; }

  int Minutes() const { return tm_.tm_min; }

  int ToMinutes() const { return tm_.tm_hour * 60 + tm_.tm_min; }

  Time operator-(const Time& rhs) {
    int min = ToMinutes() - rhs.ToMinutes();
    tm_.tm_hour = min / 60;
    tm_.tm_min = min % 60;
    return *this;
  }

  bool operator<(const Time& rhs) const {
    return ToMinutes() < rhs.ToMinutes();
  }

  bool operator>(const Time& rhs) const {
    return ToMinutes() > rhs.ToMinutes();
  }

  void operator=(const Time& rhs) {
    tm_.tm_hour = rhs.Hour();
    tm_.tm_min = rhs.Minutes();
  }

 private:
  struct tm tm_;
};

void PrintResult(int t, const Time& start, const Time& longest) {
  std::cout << "Day #" << t << ": the longest nap starts at "
            << std::setfill('0') << std::setw(2) << start.Hour() << ":"
            << std::setfill('0') << std::setw(2) << start.Minutes()
            << " and will last for ";

  if (longest.Hour() != 0)
    std::cout << longest.Hour() << " hours and ";
  std::cout << longest.Minutes() << " minutes." << std::endl;
}

void Solution(std::istream& cin) {
  int n;
  for (auto t = 1; cin >> n; t++) {
    cin.ignore(1, '\n');
    //                   start , end
    std::vector<std::pair<Time, Time>> times;
    for (auto i = 0; i < n; i++) {
      std::string line;
      getline(cin, line);
      times.push_back({Time(line.substr(0, 5)), Time(line.substr(6, 5))});
    }

    times.push_back({Time("10:00"), Time("10:00")});
    times.push_back({Time("18:00"), Time("18:00")});

    std::sort(times.begin(), times.end());

    Time nap_start, nap_duration_max;
    for (auto i = 1; i < times.size(); i++) {
      auto duration = times[i].first - times[i - 1].second;
      if (duration > nap_duration_max) {
        nap_duration_max = duration;
        nap_start = times[i - 1].second;
      }
    }

    PrintResult(t, nap_start, nap_duration_max);
  }
}

#if !defined(GTEST_TEST)
int main(int argc, char* argv[]) {
  Solution(std::cin);
  return 0;
}
#endif  // !defind(GTEST_TEST)
